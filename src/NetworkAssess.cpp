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

#include "../include/NetworkFunctions.h"

int main()
{
    enableRawMode();
    initWindow();

    //---------Key Data Structures and Variables------------
    //------------------------------------------------------
    LIST<Period> networkPeriods; //Stores recorded network latencies in each node
    VECT<Flag> flags;            //stores all of the flags before they are sorted into periods

    //this vector will contain all of the arguements passed on from the first line of the date file
    //args[0] = number of latencies
    //args[1] = total time
    //args[2] = frequency of latency data
    //args[3] = expected high latency periods
    VECT<int> args;

    //----Reading in data.txt and storing flags in DLL---
    //-----Potentially put below code in a function-------
    IFST inData;
    inData.open("DataGen/data/data.txt");

    char line[20];

    if (inData.is_open())
    {
        //----This will read the first line from data.text---
        //-----and save the arguements to a vector-------

        for (int i = 0; i < 4; i++)
        {
            inData.getline(line, 20);
            args.push_back(atoi(line));
        }

        //----this will read through the entire set of data ---
        Info info = Info();
        info.freq = args[2];
        Flag flag = Flag();
        char cmd;
        for (int j = 1; j <= 12; j++)
        {
            Period per = Period();
            per.tPeriod = 12;
            networkPeriods.push_front(per);
            for (int k = 1; k <= 2880; k++)
            {
                inData.getline(line, 20);
                if (checkLat(atoi(line)))
                {
                    Bar bar = Bar();
                    bar.r = 1;
                    flag = Flag();
                    flag.start = k;
                    while (checkLat(atoi(line)))
                    {
                        flag.latencies.push_back(atoi(line));
                        flag.numLats++;
                        inData.getline(line, 20);
                        k++;
                    }
                    flag.avgLatCalculation();
                    bar.bars = (int)(flag.avgLat / 10);
                    per.flags.push_back(flag);
                    networkPeriods.pop_front();
                    networkPeriods.push_front(per);
                    if (j > 1)
                    {
                        flag.prob = calcProb(networkPeriods);
                        if (flag.prob < 80)
                        {
                            info.netf++;
                        }
                    }
                    info.time = ((j - 1) * 3600 * 12) + (k * info.freq);
                    cmd = 'a';
                    updateWin(bar, per, flag, info, &cmd);
                }
                else if (k % 20 == 0)
                {
                    info.time = ((j - 1) * 3600 * 12) + (k * info.freq);
                    Bar bar = Bar();
                    bar.r = 2;
                    bar.bars = (int)(atoi(line) / 5);
                    updateWin(bar, per, flag, info, &cmd);
                    //pass info
                }
            }
        }

        inData.close();
    }
    else
    {
        COUT << "Error opening the input file" << ENDL;
        return 0;
    }

    disableRawMode();
    return 0;
}
