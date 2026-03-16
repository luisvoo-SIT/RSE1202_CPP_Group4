#pragma once
#include <iostream>
using namespace std;

class TimeControl {
private:
    int PlotTime;
    int GlobalTime;

public:
    TimeControl();

    void advanceTime();
    void resetTime();
    void displayTime() const;

    int getDay() const;
    int getSeason() const;
};