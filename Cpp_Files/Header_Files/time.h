#pragma once
#include <iostream>
using namespace std;

class TimeControl {
protected:
    int PlotTime=0;
    int GlobalTime=0;

public:
    void advancePlotTime(int PlotTime);
    void resetPlotTime(int PlotTime);
/*
    void advanceGlobalTime();
    void resetGlobalTime();
*/
    int getPlotTime() const;
    //int getGlobalTime() const;
};