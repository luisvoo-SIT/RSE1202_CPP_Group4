#ifndef ACTUATORS_H
#define ACTUATORS_H
#include <iostream>
#include <iomanip> 
#include <string>
using namespace std;

class Actuator
{
protected:
    int actuatorLevel;

public:
    // Constructor
    Actuator();

    // Destructor
    virtual ~Actuator();
    
    // Internal setter, it writes a value into actuatorLevel
    void adjustActuatorLevel(int value);

    // Method to display actuator level
    void displayActuatorLevel(); 

    // Virtual function, derived class overrides the value inside here. (This enables polymorphism)
    virtual void adjust(int &currentValue) = 0;
};

#endif