#include "Header_Files/TimeControl.h"

TimeControl * TimeControl::instance = nullptr;

TimeControl::TimeControl() 
{
    currentDay = 0;
}

TimeControl * TimeControl::getInstance() 
{
    if (instance == nullptr) 
    {
        instance = new TimeControl();
    }
    return instance;
}

int TimeControl::getCurrentDay() const 
{
    return currentDay;
}

void TimeControl::advanceTime(int days) 
{
    currentDay += days;
    std::cout << "\n>>> Time skipped by " << days << " day(s). Current: Day " << currentDay << " <<<\n";
}

void TimeControl::resetTime() {
    currentDay = 0;
    std::cout << "\n>>> Time reset to Day 0. <<<\n";
}