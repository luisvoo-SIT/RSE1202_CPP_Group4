#ifndef CONTROLS_H
#define CONTROLS_H
#include "Actuators.h"
#include <sstream>
#include <limits>

// Derived class: WaterSystemControl
class WaterSystemControl : public Actuator {
public:
    // Function to adjust water level that takes in current water level as parameter
    void adjust(int &currentValue) override;
};

// Derived class: TempControl
class TempControl : public Actuator {
public:
    // Function to adjust temperature that takes in current temperature level as parameter
    void adjust(int &currentValue) override;
};

// Derived class: HumidityControl
class HumidityControl : public Actuator {
public:
    // Function to adjust humidity that takes in current humidity level as parameter
    void adjust(int &currentValue) override;
};

// Derived class: UVControl
class UVControl : public Actuator {
public:
    // Function to adjust UV level that takes in current UV level as parameter
    void adjust(int &currentValue) override;
};

#endif