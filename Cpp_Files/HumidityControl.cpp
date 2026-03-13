#include "Header_Files/HumidityControl.h"

void HumidityControl::adjustHumidity(float &currentHum)
{
    // Declare new variable for new humidity level (newHumidity)
    double newHumidity;

    // Prompt user to enter new humidity level and store in newHumidity variable
    cout << "Enter new humidity level: ";
    cin >> setprecision(1) >> newHumidity;

    adjustActuatorLevel(newHumidity); // updates actuatorLevel in base class Actuator
    currentHum = newHumidity; // update current humidity level with new value

    // Prints updated humidity level to console
    cout << ">>> Humidity level has been updated to: " << currentHum << "%" << endl;

}