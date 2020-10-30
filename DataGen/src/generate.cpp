//Author: Chase Brown
//Email: cbrown54@nd.edu

#include "../include/generator.h"

#include <iostream>

int main(int argc, char* argv[]) {
    if(argc != 3) {
        COUT << "Incorrect arguements" << ENDL;
        COUT << "example: ./generate [time] [frequency]" << ENDL;
        COUT << "[time] = int value in hours ex. 24 or 48" << ENDL;
        COUT << "[frequency] = int value in seconds ex. 60 or 15" << ENDL;
        COUT << "If we run './generate 12 60' this will generate 360 lines of data" << ENDL;
        COUT << "one line for each 60 seconds from 0 to 6 hours."
        return 0;
    }

    return 0;
}
