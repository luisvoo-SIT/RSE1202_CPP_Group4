#include "Header_Files/UvControl.h"

void UVControl::adjustUV(float &currentUV)
{
    // Declare new variable for new UV level (newUV)
    double newUV;

    // Prompt user to enter new UV level and store in newUV variable
    cout << "Enter new UV level: ";
    cin >> setprecision(1) >> newUV;

    adjustActuatorLevel(newUV); // updates actuatorLevel in base class Actuator
    currentUV = newUV; // update current UV level with new value

    cout << ">>> UV level has been updated to: " << currentUV << " units" << endl;
}