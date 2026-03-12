#include "Header_Files/Actuators.h"

// Constructor definition
Actuator::Actuator()
{
    actuatorLevel = 100; // default level (100%)
}

void Actuator::adjustActuatorLevel(int value)
{
    actuatorLevel = value; // assign actuator value to new value
}

// Function to display actuator level
void Actuator::displayActuatorLevel()
{
    cout << ">>>Current actuator level is set to: " << actuatorLevel << "%" << endl;
}