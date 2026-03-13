#ifndef MOISTURECONTROL_H
#define MOISTURECONTROL_H
#include "Actuators.h" // Inherit from Base class: Actuator

// Derived class: MoistureControl
class MoistureControl : public Actuator
{
    public:
        // Function to adjust moisture that takes in current moisture level as parameter
        void adjustMoisture(float &currentMoist);

};

#endif