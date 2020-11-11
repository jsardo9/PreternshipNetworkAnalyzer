/*************************************
 * File name: Period.h
 * Authors: Jacob Sardo
 * Emails: jsardo@nd.edu
 *
 * This file contains the Period struct which
 * contains flags from a specific time interval from the network log
 * ***********************************/
#include <iostream>
#include <vector>
#include "Flag.h"

#define VECT std::vector;

struct Period{
  int tPeriod; //Time period in which the period covers (in hrs)
  VECT<Flag> flags; //list of all flags which occurred during tPeriod

//-----------------Constructors-------------------------
//------------------------------------------------------
  Period() : tPeriod(), flags() {}

  Period(int tIn, std::vector<Flag> flagsIn) : tPeriod(tIn), flags(flagsIn) {}


//-----------------Ostream Overload Function------------
  friend std::ostream& operator<<(std::ostream& output, const Period& thePeriod){
    output << "Time Period: " << thePeriod.tPeriod << " hours" << " | Flags: " << std::endl;
    for (unsigned int i = 0; i < thePeriod.flags.size(); ++i) {
      output << thePeriod.flags[i];
    }
     return output;
  }
};
