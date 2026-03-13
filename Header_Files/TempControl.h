#ifndef TEMPCONTROL_H
#define TEMPCONTROL_H
#include "Actuators.h"

// Derived class: TempControl
class TempControl : public Actuator
{
    public:
        // Function to adjust temperature that takes in current temperature level as parameter
        void adjustTemperature(float &currentTemp);

};

#endif