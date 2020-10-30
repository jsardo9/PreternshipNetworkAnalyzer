/*************************************
 * File name: NetworkAssess.cpp
 * Authors: Jacob Sardo
 * Emails: jsardo@nd.edu
 *
 * This file contains the main driver Function
 * in which pattern recognition is applied to
 * flagged high latency times in the Network Log
 * ***********************************/
#include <iostream>
#include <fstream>
#include <string>
#include <list>


int main() {
//---------Key Data Structures and Variables------------
//------------------------------------------------------
list<int> networkLats; //Stores recorded network latencies in each node
int tInterval; //Time interval between each recorded latency from "networkLats"



//----Reading in NetworkLog.txt and storing it in DLL---
//------------------------------------------------------
fstream networkLog;
int nLats; //number of latencies in the network log
networkLog.open("../include/NetworkLog.txt", ios::in)

// retreving first line from NetworkLog.txt which contains information regarding
// total time contained in log (hrs) and the time interval between recordings (seconds)
string hrs;
getline(networkLog, hrs, '\t');
string interval;
getline(networkLog, interval);

  
tInterval = (int)interval;
nLats = ((int)hours) * 3600)/ tInterval;

// reading latencies into networkLats
string currLatency;
    for (int i = 0; i < nLats){  //read data from file object and put it into string.
       getline(networkLog, currLatency)
       networkLats.push_back((int)currLatency)
    }

networkLog.close; //closing Network Log txt file
//------------------------------------------------------
//------------------------------------------------------

  return 0;
}
