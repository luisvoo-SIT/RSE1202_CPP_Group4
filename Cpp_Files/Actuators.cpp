#include "Header_Files/Actuators.h"

Actuator::Actuator()
{
    actuatorLevel = 0;
}

Actuator::~Actuator()
{
    // code if needed
}

void Actuator::adjustActuatorLevel(int value)
{
    actuatorLevel = value;
}

void Actuator::displayActuatorLevel()
{
    cout << ">>> Current actuator level is set to: " << actuatorLevel << " %" << endl;
}