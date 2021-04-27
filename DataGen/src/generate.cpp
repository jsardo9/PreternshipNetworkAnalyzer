/*************************************
 * File name: generate.cpp
 * Authors: Jacob Sardo and Chase Brown
 * Emails: jsardo@nd.edu and cbrown54@nd.edu
 *
 * This file contains the main driver Function
 * for generating a new set of test network logs
 * ***********************************/

#include "../include/generator.h"

int main(int argc, char *argv[])
{
    //this is a simple help statement if the user does not include the correct arguements
    if (argc != 5)
    {
        COUT << "Incorrect arguements" << ENDL;
        COUT << "example: ./generate [time] [frequency] [expected] [seed]" << ENDL;
        COUT << "[time] = int value in hours ex. 24 or 48" << ENDL;
        COUT << "[frequency] = int value in seconds ex. 60 or 15" << ENDL;
        COUT << "[expected] = int value in hours ex. 12 or 24 **[time] % [expected] == 0**" << ENDL;
        COUT << "[seed] = int value between 1-9999" << ENDL;
        COUT << "If we run './generate 12 60 4 1920' this will generate 360 lines of data" << ENDL;
        COUT << "one line for each 60 seconds from 0 to 6 hours." << ENDL;
        return 0;
    }
    else
    {
        int time = atoi(argv[1]);
        int freq = atoi(argv[2]);
        int expected = atoi(argv[3]);
        int seed = atoi(argv[4]);
        int numData = 0;
        numData = generate(time, freq, expected, seed);
        //COUT << numData << " data entries were generated" << ENDL;
    }

    return 0;
}
