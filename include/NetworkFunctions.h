/*************************************
 * File name: NetworkFunctions.h
 * Authors: Jacob Sardo and Chase Brown
 * Emails: jsardo@nd.edu and cbrown54@nd.edu
 *
 * This file contains the functions to find flags
 * and split them up into their respective periods
 * ***********************************/

#ifndef NETWORKFUNCTIONS_H
#define NETWORKFUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <fstream>

#define COUT std::cout;
#define ENDL std::endl;
#define IFST std::ifstream;
#define RD std::getline;
#define STR std::string;

VECT collectFlags() {
    VECT<int> flags;

    
    return flags;
}

int checkFlag(int latency) {
    if(latency > 100) {
        return 1;
    }
    return 0;
}



