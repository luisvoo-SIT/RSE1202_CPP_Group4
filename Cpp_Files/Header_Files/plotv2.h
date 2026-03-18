#ifndef PLOT_H
#define PLOT_H
#include <iostream>
#include <iomanip> 
#include <string>

using namespace std;

// Represents one 3x3 Sector
class Plot {

    public:
        float currentTemp = 20.0;
        float currentHum = 60.0;
        int currentWater = 0;
        bool fertilizersprayed = false;
        bool pestsprayed = false;
        bool herbsprayed = false;
        string cropName = "Empty";

        enum Status { SEED, PLANT, DEAD, EMPTY};
        const string StatusNames[4] = {"Seed", "Plant", "Dead", "Empty"};
        int cropstatus=3;

        char symbol = ' ';
        int PlotTime = 0; //how long the crop has been planted for - will be cleared for timecontrol.cpp

        // Default constructor
        Plot() = default;

        // Plot constructor
        Plot(float cTemp, float cHum, unsigned int cWater){
            currentTemp = cTemp;
            currentHum = cHum;
            currentWater = cWater;
        }
};
#endif