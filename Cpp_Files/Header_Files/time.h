#pragma once
#include <iostream>
using namespace std;

class TimeControl {
private:
    int PlotTime;
    int GlobalTime;

public:
    TimeControl();

    void advancePlotTime();
    void resetPlotTime();
    int getPlotTime() const;
    int getGlobalTime() const;
};