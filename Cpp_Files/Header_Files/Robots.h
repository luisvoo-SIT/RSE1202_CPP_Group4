#pragma once
#include <string>

using namespace std;

class Robot {
protected:
    string id;
    string name;

public:
    Robot(const string& id, const string& name);
    ~Robot() {}

    void statusReport() const;

    bool          getIsOperational() const { return isOperational; }
    double        getBatteryLevel()  const { return batteryLevel;  }
    const string& getName()          const { return name;          }




};