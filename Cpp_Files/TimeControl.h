#pragma once
#include <iostream>

class TimeControl 

{
private:
    int currentDay;
    static TimeControl* instance;
    TimeControl();

public:
    TimeControl(const TimeControl&) = delete;
    TimeControl& operator=(const TimeControl&) = delete;

    static TimeControl* getInstance();
    int getCurrentDay() const;
    void advanceTime(int days = 1);
    void resetTime();
};