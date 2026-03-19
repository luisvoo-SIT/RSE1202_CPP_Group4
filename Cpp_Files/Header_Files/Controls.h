#ifndef CONTROLS_H
#define CONTROLS_H
#include "Actuators.h"
#include <sstream>
#include <limits>

class WaterSystemControl : public Actuator {
public:
    void adjustWater(unsigned int &currentWater);
};

class TempControl : public Actuator {
public:
    void adjustTemperature(unsigned int &currentTemp);
};

class HumidityControl : public Actuator {
public:
    void adjustHumidity(unsigned int &currentHum);
};

class UVControl : public Actuator {
public:
    void adjustUV(unsigned int &currentUV);
};

#endif