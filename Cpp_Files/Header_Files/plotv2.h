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
        float currentWater = 50.0;
        string cropName = "Empty";
        char symbol = ' ';

        // Default constructor
        Plot() = default;

        // Plot constructor
        Plot(float cTemp, float cHum, float cWater){
            currentTemp = cTemp;
            currentHum = cHum;
            currentWater = cWater;
        }
};
#endif