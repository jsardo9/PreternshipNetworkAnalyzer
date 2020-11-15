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

int main() {

//---------Key Data Structures and Variables------------
//------------------------------------------------------
std::list<Period> networkPeriods; //Stores recorded network latencies in each node
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

    // inData.getline(line, 20);
    // COUT << line << ENDL;
    for(int i = 0; i < 4; i++) {
        inData.getline(line, 20);
        args.push_back(atoi(line));
    }
    for(int arg : args) {
        COUT << arg << ENDL;
    }
    COUT << "args done" << ENDL;

    // COUT << args.at(0) << ENDL;
    //----this will read through the entire set of data ---
    for(int i = 1; i <= args.at(0); i++) {
        inData.getline(line, 20);
        // COUT << line << ENDL;
        if(checkLat(atoi(line))) {
            Flag flag = Flag();
            flag.start = i;
            while(checkLat(atoi(line))) {
                flag.latencies.push_back(atoi(line));
                flag.numLats++;
                inData.getline(line, 20);
                i++;
            }
            flag.avgLatCalculation();
            COUT << "flag made with avg: " << flag.avgLat << ENDL;

        }
    }
    inData.close();
}
else {
    COUT << "Error opening the input file" << ENDL;
    return 0;
}


//-----Potentially put below code in a function-------
// int count;
// int prev;
//
// for(count = 0; !inData.eof(); count++) {
//   	getline(inData, line);
//   	COUT << line << ENDL;
//   	if(checkFlag(atoi(line))) {
// 		Flag temp = new Flag();
// 		getline(inData, line);
// 		temp.start = count;
// 		temp.latencies.push_back(atoi(line));
// 		temp.numLats = 1;
// 		while(checkFlag(atoi(line)) == 1) {
// 			getline(inData, line);
// 			temp.latencies.push_back(atoi(line));
// 			temp.numLats++;
// 			count++;
// 		}
// 		flags.push_back(temp);
//   	}
// }
// inData.close()

// for(Flag flag : flags) {
// 	//here we will compare each the starting points of the flag to determine which period it should go in.
// }









// reading latencies into networkLats

// int currInPeriod = 0; // keeps track when we reach the end of a current period
// Period currPeriod;
// std::vector<Flag> currFlags; // list of flags within the current period
// bool withinFlag = false; //true while index is currently within a flag
//
//     for (int i = 0; i < nLats; ++i){
//       if (currInPeriod == 0) {
//          currPeriod = Period(tPeriod, currFlags); // Creating a new Period if we are at index 0 of a Period
//       }
//
//        //pulling current latency
//        std::string currLatency;
//        getline(networkLog, currLatency);
//        int currLat = std::stoi(currLatency);
//
//        if (currLat > 100) {
//          if (!withinFlag) { // this means its the start of a new flag
//            withinFlag = true;
//            currFLags = std::vector<Flag>();
//          }
//       currFlags.push_back((int)currLatency)
//      }
//      else if (withinFlag) {// end of a flag means we need to add flag to current period
//        withinFlag = false;
//
//      }
//
//        currInPeriod = (currInPeriod + 1) % latsPerPeriod; // increase the index of location in the period
//     }
// //------------------------------------------------------
//
// networkLog.close; //closing Network Log txt file


  return 0;
}
