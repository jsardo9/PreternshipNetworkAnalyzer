
/*************************************
 * File name: generator.h
 * Authors: Jacob Sardo and Chase Brown
 * Emails: jsardo@nd.edu and cbrown54@nd.edu
 *
 * This file contains the functions to randomly
 * generate a network log
 * ***********************************/

#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <fstream>

#define COUT std::cout
#define ENDL std::endl
#define TM std::time
#define APP std::ios_base::app
#define FST std::ofstream

int flags = 0;
FST data;

//this function will randomly decide a random value should be added or subtracted
int addOrSub() {
    int random = rand() % 2; //0 = sub, 1 = add;
    if(random) {
        return 1;
    }
    else {
        return 0;
    }
}

//this function will genera
int genLat(int lat) {
    int change = rand() % 10;
    int dir = addOrSub();
    if(dir) {
        lat += change;
    }
    else {
        lat -= change;
    }
    return lat;
}

int genSpike(int freq) {
    int numAdded = 0;
    int spikeTime = 60 * ((rand() % 5) + 3); //average time for a spike is 2 - 7 min (converted to seconds)
    // COUT << "spike time: " << spikeTime << ENDL;
    int lat = (rand() % 500) + 150; //generate random latency between 150 - 650
    // FST data;
    // data.open("data.txt", APP);

    while(spikeTime >= freq) {
        data << lat << "\n";
        lat = genLat(lat);
        spikeTime -= freq;
        numAdded++;
    }
    // COUT << "added: " << numAdded << ENDL;
    // data.close();
    flags++;
    return numAdded;
}


int generate(int time, int freq, int expected, int seed) {
    srand(seed);
    //num is going to be the number of data points generated
    int num = (time * 60 * 60) / freq;

    //prev is to make sure we do not generate spikes on top of one another... they need to have some space between them in order to
    //create the most accurate results.
    int prev = 0;

    data.open("data.txt", APP); //opens the file in append mode

    data << num << '\n';
    data << time << '\n';
    data << freq << '\n';
    data << expected << '\n';
    int lat = 50;
    for(int i = 0; i < num; i++) {
        //this is checking to see if the previous was greater than 30min ago and has a random 1/10 chance of triggering a spike in latency.
        //OR if there is an expected spike.
        if((rand() % (num/4) == 1)  || (((i * freq * 100) / 3600)  % (expected * 100) == 0 && ((i * freq * 100) / 3600)  % (100) == 0)) { //prev >= ((1 / (60 / freq)) * 30) &&
            COUT << ((i * freq * 100) / 3600) << ENDL;
            COUT << "making spike" << ENDL;
            int add = genSpike(freq);
            i += add - 1;
            prev = 0;
        }
        else {
            // COUT << "making data" << ENDL;
            lat = genLat(40);
            // data.open("data.txt", APP); //this is not ideal... I need to better understand file writing...
            data << lat << '\n';
            // data.close();
            prev++;
        }
    }
    COUT << "made: " << flags << " flags" << ENDL;
    data.close();
    return num;
}

#endif
