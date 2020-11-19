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

#include "window.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>
#include <termios.h>
#include <unistd.h>

#define COUT std::cout
#define ENDL std::endl
#define IFST std::ifstream
#define STR std::string
#define LIST std::list
#define ADV std::advance
#define ABS std::abs

int calcProb(LIST<Period> periods) {
    int prob = 0;
    Period cur = periods.front();
    int diff = 0;

    periods.pop_front();
    Period temp = periods.front();
    diff = (int)(ABS(temp.flags.front().start - cur.flags.back().start) / 10);
    for(Flag flag : temp.flags) {
        if(diff < 10) {
            prob = 100 - (rand()%10) - 1;
        }
        else if(diff < 50) {
            prob = 100 - (rand()%25) - 10;
        }
        else if(diff < 100) {
            prob = 100 - (rand()%50) - 25;
        }
        else {
            prob = (rand() % 25) + 2;
        }
    }
    return prob;
}

int checkLat(int latency) {
    if(latency > 100) {
        return 1;
    }
    return 0;
}

#endif
