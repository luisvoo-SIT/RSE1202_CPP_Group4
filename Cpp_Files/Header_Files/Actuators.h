#ifndef ACTUATORS_H
#define ACTUATORS_H
#include <iostream>
#include <iomanip> 
using namespace std;

// Base class: Actuator
class Actuator
{
protected:
    double actuatorLevel; // actuator level (e.g. water level, light level)

public:
    // Constructor
    Actuator();

    // Virtual method (function) to adjust actuator level (during runtime)
    virtual void adjustActuatorLevel(double value);

    // Method to display actuator level
    void displayActuatorLevel();

};


#endif