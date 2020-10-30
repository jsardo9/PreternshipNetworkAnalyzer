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

void genSpike(fstream& data, int freq) {

}

int generate(int time, int freq, int expected) {
    srand(time(NULL));

    int num = (time * 60 * 60) / freq;
    int prev = 0;
    FST data("data.txt");

    data << num << "\t" << time << "\t" << freq << '\t' << expected << "\n";

    for(int i = 0; i < num; i++) {
        int lat = 0;

        if(prev >= ((1 / (freq / 60)) * 30) & (rand() % 10) == 1 ) {
            prev = 0;
        }
        else {
            prev++;
        }


        data << lat << '\n';
    }
    data.close();
    return numData;
}



#endif
