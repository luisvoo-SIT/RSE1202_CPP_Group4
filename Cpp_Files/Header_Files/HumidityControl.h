#ifndef HUMIDITYCONTROL_H
#define HUMIDITYCONTROL_H
#include "Actuators.h"

// Derived class: HumidityControl
class HumidityControl : public Actuator
{
    public:
        // Function to adjust humidity that takes in current humidity level as parameter
        void adjustHumidity(float &currentHum);
};


#endif