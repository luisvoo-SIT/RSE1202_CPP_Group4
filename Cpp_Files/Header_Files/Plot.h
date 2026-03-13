#ifndef PLOT_H
#define PLOT_H
#include <iostream>
#include <iomanip> 
using namespace std;

// Represents one 3x3 Sector
class Plot {

    public:
        float currentTemp;
        float currentHum;
        float currentWater;
    
        Plot(float cTemp, float cHum, float cWater){
            currentTemp = cTemp;
            currentHum = cHum;
            currentWater = cWater;
        }
};
#endif