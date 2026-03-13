#ifndef ACTUATORS_H
#define ACTUATORS_H
#include <iostream>
using namespace std;

// Base class: Actuator

class Actuator
{
protected:
    int actuatorLevel; // actuator level (e.g. water level, light level)

public:
    // Constructor
    Actuator();

    // Virtual method (function) to adjust actuator level (during runtime)
    virtual void adjustActuatorLevel(int value);

    // Method to display actuator level
    void displayActuatorLevel();

};


#endif
