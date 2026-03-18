#include "Header_Files/Actuators.h"

// Constructor definition
Actuator::Actuator()
{
    actuatorLevel = 0; // default level (0%)  (in future need to replace with plot varaibles pointers)
}

// Destructor definition
Actuator::~Actuator()
{
   // code if needed
}

void Actuator::adjustActuatorLevel(unsigned int value)
{
    actuatorLevel = value; // assign actuator value to new value
}

// Function to display actuator level
void Actuator::displayActuatorLevel()
{
    cout << ">>> Current actuator level is set to: " << static_cast<unsigned int>(actuatorLevel) << "%" << endl;
}
