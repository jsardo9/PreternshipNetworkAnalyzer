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


int main() {
//----Reading in NetworkLog.txt and storing it in DLL---
//------------------------------------------------------
  list<int> networkEvents;

  fstream networkLog;
  networkLog.open("../include/NetworkLog.txt", ios::in)
  string netEvent;
      while(getline(networkLog, netEvent)){  //read data from file object and put it into string.
        // add to list
      }
  networkLog.close; //closing Network Log txt file

  return 0;
}

