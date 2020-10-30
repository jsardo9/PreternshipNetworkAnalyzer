//Author: Chase Brown
//Email: cbrown54@nd.edu

#ifndef GENERATE_H
#define GENERATE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <fstream>

#define COUT std::cout;
#define ENDL std::endl;
#define FST std::ofstream;



int genSpike(fstream& data, int freq) {
    int numAdded;
    int spikeTime = 60 * ((rand() % 5) + 3); //average time for a spike is 2 - 7 min (converted to seconds)

    return numAdded;
}

int generate(int time, int freq, int expected) {
    srand(time(NULL));

    int num = (time * 60 * 60) / freq;
    

    
    int prev = 0;
    FST data("data.txt");

    data << num << "\t" << time << "\t" << freq << '\t' << expected << "\n";
    int lat = 0;
    for(int i = 0; i < num; i++) {
        //this is checking to see if the previous was greater than 30min ago and has a random 1/10 chance of triggering a spike in latency.
        //OR if there is an expected spike.
        if((prev >= ((1 / (freq / 60)) * 30) && (rand() % 10) == 1 ) ||  time % expected == 0) {  
            int add = genSpike();
            i += add - 1;
            prev = 0;
        }
        else {
            int change = rand() % 20;
            int addOrSub = rand() % 2; //0 = sub, 1 = add;
            if(addOrSub) {
                lat += change; 
            }
            else {
                lat -= change;
            }
            data << lat << '\n';
            prev++;
        }


    }
    data.close();
    return numData;
}



#endif
