#include "TempControl.h"

void TempControl::adjustTemperature(float &currentTemp)
{
    // Declare new variable for new temperature level (newTemp)
    double newTemp;

    // Prompt user to enter new temperature level and store in newTemp variable
    cout << "Enter new temperature level: ";
    cin >> setprecision(1) >> newTemp;

    adjustActuatorLevel(newTemp); // updates actuatorLevel in base class Actuator
    currentTemp = newTemp; // update current temperature level with new value

    cout << ">>> Temperature level has been updated to: " << currentTemp << " C" << endl;
}