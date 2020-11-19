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

int checkLat(int latency) {
    if(latency > 100) {
        // COUT << latency << ENDL;
        return 1;
    }
    return 0;
}

#endif
