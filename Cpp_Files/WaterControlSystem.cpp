#include "WaterSystemControl.h"

void WaterSystemControl::adjustWater(float &currentWater) 
{
    // Declare new variable for new water level (newWater)
    double newWater;

    // Prompt user to enter new water level and store in newWater variable
    cout << "Enter new water level: ";
    cin >> setprecision(1) >> newWater;


    adjustActuatorLevel(newWater); // updates actuatorLevel in base class Actuator
    currentWater = newWater; // update current water level with new value

    // Prints updated water level to console
    cout << ">>> Water level has been updated to: " << currentWater << " litres" << endl;



}