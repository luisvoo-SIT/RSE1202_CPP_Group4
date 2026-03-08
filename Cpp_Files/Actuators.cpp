#include "Actuators.h"

// Implementation of Base class (Sensor)
Actuator::Actuator(string name)
{
    actuatorName = name;  //assigns the object "sensorName" to string variable "name"
}

Actuator::~Actuator()
{
    // Destructor (empty but good practice)
}

