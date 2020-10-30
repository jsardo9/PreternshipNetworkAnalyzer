//Author: Chase Brown
//Email: cbrown54@nd.edu

#ifndef GENERATE_H
#define GENERATE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <fstream>

#define COUT std::cout;
#define ENDL std::endl;
#define FST std::ofstream;

int addOrSub() {
    int random = rand() % 2; //0 = sub, 1 = add;
    if(random) {
        return 1;
    }
    else {
        return 0;
    }
}

int genLat(int lat) {
    int change = rand() % 20;
    int dir = addOrSub();
    if(dir) {
        lat += change;
    }
    else {
        lat -= change;
    }
    return lat;
}

int genSpike(FST& data, int freq) {
    int numAdded = 0;
    int spikeTime = 60 * ((rand() % 5) + 3); //average time for a spike is 2 - 7 min (converted to seconds)
    int lat = (rand() % 500) + 150; //generate random latency between 150 - 650
    while(spikeTime >= freq) {
        data << lat << "\n";
        lat = genLat(lat);
        spikeTime -= freq;
        numAdded++;
    }
    return numAdded;
}

int generate(int time, int freq, int expected) {
    srand(time(NULL));
    //num is going to be the number of data points generated
    int num = (time * 60 * 60) / freq;

    //prev is to make sure we do not generate spikes on top of one another... they need to have some space between them in order to
    //create the most accurate results.
    int prev = 0;
    FST data;
    data.open("data.txt", ios::app); //opens the file in append mode

    data << num << "\t" << time << "\t" << freq << '\t' << expected << "\n";
    int lat = 0;
    for(int i = 0; i < num; i++) {
        //this is checking to see if the previous was greater than 30min ago and has a random 1/10 chance of triggering a spike in latency.
        //OR if there is an expected spike.
        if((prev >= ((1 / (freq / 60)) * 30) && (rand() % 10) == 1 ) ||  time % expected == 0) {
            int add = genSpike(data, freq);
            i += add - 1;
            prev = 0;
        }
        else {
            lat = genLat(lat);
            data << lat << '\n';
            prev++;
        }
    }
    data.close();
    return num;
}

#endif
