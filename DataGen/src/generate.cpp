//Author: Chase Brown
//Email: cbrown54@nd.edu

#include "../include/generator.h"

#include <iostream>

int main(int argc, char* argv[]) {
    if(argc != 4) {
        COUT << "Incorrect arguements" << ENDL;
        COUT << "example: ./generate [time] [frequency]" << ENDL;
        COUT << "[time] = int value in hours ex. 24 or 48" << ENDL;
        COUT << "[frequency] = int value in seconds ex. 60 or 15" << ENDL;
        COUT << "[expected] = int value in hours ex. 12 or 24 **[time] % [expected] == 0**" << ENDL
        COUT << "If we run './generate 12 60' this will generate 360 lines of data" << ENDL;
        COUT << "one line for each 60 seconds from 0 to 6 hours."
        return 0;
    }
    else {
        int time = atoi(argv[1]);
        int freq = atoi(argv[2]);
        int expected = atoi(argv[3]);
        int numData = 0;
        numData = generate(time, freq, expected);

        COUT << numData << " data entries were generated" << ENDL;
    }

    return 0;
}
