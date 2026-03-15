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

    const string& getName() const { return name; }
    const string& getId()   const { return id;   }
};