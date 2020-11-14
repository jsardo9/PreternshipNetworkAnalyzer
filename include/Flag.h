/*************************************
 * File name: Flag.h
 * Authors: Jacob Sardo
 * Emails: jsardo@nd.edu
 *
 * This file contains the Flag class which
 * contains information of a flagged
 * set of spiking latencies
 * ***********************************/
#include <iostream>
#include <vector>

struct Flag{
    int start; // starting index of the spike
    std::vector<int> latencies; // list of spiked latencies (use to calculate mean latency during the spike)
    int numLats; // number of spiking latencies
    double avgLat; // the overage latency over the course of the spike

//-----------------Constructors-------------------------
//------------------------------------------------------
    Flag() : start(), latencies(), numLats(), avgLat() {}

    Flag(int startIn, std::vector<int> latsIn, int nLats) : start(startIn), latencies(latsIn), numLats(nLats), avgLat(0) {
      avgLatCalculation();
    }

//-----------------Methods-------------------------
//-------------------------------------------------
  void avgLatCalculation() {
    for (unsigned int i = 0; i < latencies.size(); ++i) {
      avgLat = avgLat + latencies[i] * 1/(double)numLats;
    }
  }

//-----------------Ostream Overload Function------------
    friend std::ostream& operator<<(std::ostream& output, const Flag& theFlag){
    	 output << "Start Index: " << theFlag.start << " | Mean Latency: " << theFlag.avgLat << " | #Latencies: " << theFlag.numLats << std::endl;
       return output;
    }

};
