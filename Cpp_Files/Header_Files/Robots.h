#pragma once
#include <string>
#include <iostream>

using namespace std;

class Robot {
protected:
    string id;
    string name;
    double batteryLevel;
    bool   isOperational;

    void consumeBattery(double amount);

public:
    Robot(const string& id, const string& name);

    virtual ~Robot();

    virtual void performTask() = 0;

    virtual void recharge();
    virtual void shutdown();
    virtual void statusReport() const;

    bool          getIsOperational() const { return isOperational; }
    double        getBatteryLevel()  const { return batteryLevel;  }
    const string& getName()          const { return name;          }




};