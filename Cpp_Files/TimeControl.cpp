#include "Header_Files/time.h"


void TimeControl::advancePlotTime(int PlotTime) {
    PlotTime++;
}

void TimeControl::resetPlotTime(int PlotTime) {
    PlotTime = 0;
}
/* 
void TimeControl::advanceGlobalTime(int PlotTime) {
    GlobalTime++;
}

void TimeControl::resetGlobalTime(int PlotTime) {
    GlobalTime = 0;
}
*/
int TimeControl::getPlotTime() const { return PlotTime; }
//int TimeControl::getGlobalTime() const { return GlobalTime; }