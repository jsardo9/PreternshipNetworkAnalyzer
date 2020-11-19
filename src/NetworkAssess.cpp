/*************************************
 * File name: NetworkAssess.cpp
 * Authors: Jacob Sardo and Chase Brown
 * Emails: jsardo@nd.edu and cbrown54@nd.edu
 *
 * This file contains the main driver Function
 * in which pattern recognition is applied to
 * flagged high latency times in the Network Log
 * ***********************************/
#include <iostream>
#include <fstream>
#include <string>
#include <list>

#include "../include/NetworkFunctions.h"
// #include "../include/window.h"

int main() {
    enableRawMode();
    // printf("this is a test");
    // fflush(NULL);
    initWindow();

    //---------Key Data Structures and Variables------------
    //------------------------------------------------------
    LIST<Period> networkPeriods; //Stores recorded network latencies in each node
    VECT<Flag> flags; //stores all of the flags before they are sorted into periods

    //this vector will contain all of the arguements passed on from the first line of the date file
    //args[0] = number of latencies
    //args[1] = total time
    //args[2] = frequency of latency data
    //args[3] = expected high latency periods
    VECT<int> args;

    //----Reading in data.txt and storing flags in DLL---
    //-----Potentially put below code in a function-------
    IFST inData;
    inData.open("DataGen/data.txt");

    char line[20];

    if(inData.is_open()) {
        //----This will read the first line from data.text---
        //-----and save the arguements to a vector-------

        for(int i = 0; i < 4; i++) {
            inData.getline(line, 20);
            args.push_back(atoi(line));
        }
        // for(int arg : args) {
        //     COUT << arg << ENDL;
        // }
        // COUT << "args done" << ENDL;

        Info info = Info();
        info.time = 0;
        info.freq = args[2];
        info.netf = 0;

        Bar b = Bar();
        b.r = 2;
        b.bars = 10;
        updateWin(b, flag, info);




        // //----this will read through the entire set of data ---
        // for(int i = 1; i <= args.at(0); i++) {
        //     inData.getline(line, 20);
        //     // COUT << line << ENDL;
        //     if(checkLat(atoi(line))) {
        //         Flag flag = Flag();
        //         flag.start = i;
        //         while(checkLat(atoi(line))) {
        //             flag.latencies.push_back(atoi(line));
        //             flag.numLats++;
        //             inData.getline(line, 20);
        //             i++;
        //         }
        //         flag.avgLatCalculation();
        //         flags.push_back(flag);
        //         COUT << "flag made with avg: " << flag.avgLat << ENDL;
        //     }
        //     else {
        //
        //     }
        // }
        inData.close();
    }
    else {
        COUT << "Error opening the input file" << ENDL;
        return 0;
    }

    //----Now we are going to begin comparing the periods and locate flags ---------

    //----lets make the periods and link them in the list --------------------------
    for(int time = 0; time < args.at(1); time += 12) {
        Period period = Period();
        period.tPeriod = 12;
        networkPeriods.push_back(period);
    }

    //----lets split the flags up into periods -------------------------------------
    for(Flag flag : flags) {
        int time = (int)((flag.start * args.at(2) / 3600)/12);
        auto front = networkPeriods.begin();
        ADV(front,time);
        front->flags.push_back(flag);
    }

    //-----Now lets compare the periods --------------------------------------------


    disableRawMode();
    return 0;
}
