#ifndef ACTUATORS_H
#define ACTUATORS_H
#include <iostream>
#include <iomanip> 
#include <string>
using namespace std;

// Base class: Actuator
class Actuator
{
protected:
    unsigned int actuatorLevel; // actuator level (e.g. water level, light level)

public:
    // Constructor
    Actuator();

    // Destructor
    virtual ~Actuator(); 

    // Virtual method (function) to adjust actuator level (during runtime)
    virtual void adjustActuatorLevel(unsigned int value);

    // Method to display actuator level
    void displayActuatorLevel();

};


#endif