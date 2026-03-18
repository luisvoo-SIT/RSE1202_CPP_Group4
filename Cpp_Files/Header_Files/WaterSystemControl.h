#ifndef WATERSYSTEMCONTROL_H
#define WATERSYSTEMCONTROL_H
#include "Actuators.h" // Inherit from Base class: Actuator

// Derived class: WaterControl
class WaterSystemControl : public Actuator
{
    public:
        // Function to adjust water level that takes in current water level as parameter
        void adjustWater(unsigned int &currentWater);  

};

#endif