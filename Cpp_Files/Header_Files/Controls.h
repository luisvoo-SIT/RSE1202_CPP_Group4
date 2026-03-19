#ifndef CONTROLS_H
#define CONTROLS_H
#include "Header_Files/Actuators.h"
#include <sstream>
#include <limits>

// Derived class: WaterSystemControl
class WaterSystemControl : public Actuator {
public:
    // Function to adjust water level that takes in current water level as parameter
    void adjustWater(unsigned int &currentWater);
};

// Derived class: TempControl
class TempControl : public Actuator {
public:
    // Function to adjust temperature that takes in current temperature level as parameter
    void adjustTemperature(unsigned int &currentTemp);
};

// Derived class: HumidityControl
class HumidityControl : public Actuator {
public:
    // Function to adjust humidity that takes in current humidity level as parameter
    void adjustHumidity(unsigned int &currentHum);
};

// Derived class: UVControl
class UVControl : public Actuator {
public:
    // Function to adjust UV level that takes in current UV level as parameter
    void adjustUV(unsigned int &currentUV);
};

#endif