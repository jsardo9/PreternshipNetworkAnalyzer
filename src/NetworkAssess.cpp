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
#include "../include/Period.h"


int main() {

//---------Key Data Structures and Variables------------
//------------------------------------------------------
std::list<Period> networkPeriods; //Stores recorded network latencies in each node

//----Reading in data.txt and storing flags in DLL---
//-----Potentially put below code in a function-------
IFST inData;
inData.open("../DataGen/data.txt");

if(!inData) {
  COUT << "Error opening the input file" << ENDL;
}

//this vector will contain all of the arguements passed on from the first line of the date file
//args[0] = number of latencies
//args[1] = total time
//args[2] = frequency of latency data
//args[3] = expected high latency periods
VECT<int> args; 


//----This will read the first line from data.text---
//-----and save the arguements to a vector-------
getline(inData, line);
size_t pos = 0;
STR delimiter = '::';

while ((pos = line.find(delimiter)) != STR::npos) {
    args.push_back(atoi(line.substr(0, pos)));
    line.erase(0, pos + delimiter.length());
}

//----this will read through the entire set of data ---
//-----Potentially put below code in a function-------
while(!inData.eof()) {
  getline(inData, line);
  COUT << line << ENDL;
  if(checkFlag) {

  }

}
inData.close()




// reading latencies into networkLats
int currInPeriod = 0; // keeps track when we reach the end of a current period
Period currPeriod;
std::vector<Flag> currFlags; // list of flags within the current period
bool withinFlag = false; //true while index is currently within a flag

    for (int i = 0; i < nLats; ++i){
      if (currInPeriod == 0) {
         currPeriod = Period(tPeriod, currFlags); // Creating a new Period if we are at index 0 of a Period
      }

       //pulling current latency
       std::string currLatency;
       getline(networkLog, currLatency);
       int currLat = std::stoi(currLatency);

       if (currLat > 100) {
         if (!withinFlag) { // this means its the start of a new flag
           withinFlag = true;
           currFLags = std::vector<Flag>();
         }
      currFlags.push_back((int)currLatency)
     }
     else if (withinFlag) {// end of a flag means we need to add flag to current period
       withinFlag = false;

     }

       currInPeriod = (currInPeriod + 1) % latsPerPeriod; // increase the index of location in the period
    }
//------------------------------------------------------

networkLog.close; //closing Network Log txt file


  return 0;
}
