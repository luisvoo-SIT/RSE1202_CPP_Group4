#ifndef ACTUATORS_H
#define ACTUATORS_H
#include <iostream>
#include <iomanip> 
#include <string>
using namespace std;

class Actuator
{
protected:
    unsigned int actuatorLevel;

public:
    // Constructor
    Actuator();

    // Destructor
    virtual ~Actuator();
    
    // Virtual method (function) to adjust actuator level (during runtime)
    virtual void adjustActuatorLevel(unsigned int value);

    // Method to display actuator level
    void displayActuatorLevel(); 

    // Pure virtual function — every derived class MUST override this.
    // This is what enables polymorphism: one function name, many behaviours.
    virtual void adjust(unsigned int &currentValue) = 0;
};

#endif