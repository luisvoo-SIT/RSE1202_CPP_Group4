#include "time.h"

time::TimeControl() {
    PlotTime = 0;
    GlobalTime = 0;
}

void TimeControl::advancePlotTime() {
    PlotTime++;
}

void TimeControl::resetPlotTime() {
    PlotTime = 0;
}

void TimeControl::advanceGlobalTime() {
    GlobalTime++;
}

void TimeControl::resetGlobalTime() {
    GlobalTime = 0;
}

int TimeControl::getPlotTime() const { return PlotTime; }
int TimeControl::getGlobalTime() const { return GlobalTime; }