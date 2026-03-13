#include "Header_Files/MoistureControl.h"

void MoistureControl::adjustMoisture(float &currentMoist)
{
    // Declare new variable for new moisture level (newMoisure)
    double newMoisture;

    // Prompt user to enter new moisture level and store in newMoisture variable
    cout << "Enter new moisture level: ";
    cin >> setprecision(1) >> newMoisture;


    adjustActuatorLevel(newMoisture); // updates actuatorLevel in base class Actuator
    currentMoist = newMoisture; // update current moisture level with new value

    // Prints updated moisture level to console
    cout << ">>> Moisture level has been updated to: " << currentMoist << "%" << endl;



}