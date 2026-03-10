#ifndef WATERINGSYSTEM_H
#define WATERINGSYSTEM_H
#include "Actuators.h" // Inherit from Base class: Actuator

// Derived class: WateringSystem
class WateringSystem : public Actuator
{
    public:
        // Function to adjust watering level that takes in int moistureLevel as argument
        void adjustWateringLevel(int moistureLevel);

};


#endif