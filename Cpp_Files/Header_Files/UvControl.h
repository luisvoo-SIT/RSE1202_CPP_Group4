#ifndef UVCONTROL_H
#define UVCONTROL_H
#include "Actuators.h"

// Derived class: UVControl
class UVControl : public Actuator
{
    public:
        // Function to adjust UV level that takes in current UV level as parameter
        void adjustUV(float &currentUV);

};

#endif