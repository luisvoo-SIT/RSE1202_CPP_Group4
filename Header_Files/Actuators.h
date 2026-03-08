#ifndef ACTUATORS_H
#define ACTUATORS_H

#include <iostream>
#include <string>

using namespace std;   

//========== Base class: Actuator ==========
class Actuator 
{
protected:
    string actuatorName;              // Name of sensor (protected so that derived class can access this)
    
public:
    Actuator(string name);            // Constructor to initialize sensor name
    virtual void readData() = 0;    // Declares readData() function intial value as 0 (can be overidden in the derived classes)
    virtual ~Actuator();              // Deconstructor 

};






#endif