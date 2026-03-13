#pragma once
#include "Robots.h"
#include <string>
#include <vector>

using namespace std;

class SprayerBot : public Robot {
public:
    enum class SprayMode { FERTILIZER, PESTICIDE, HERBICIDE, CUSTOM };

private:
    SprayMode   mode;
    double      tankCapacityL;
    double      tankLevelL;
    double      sprayRateL_per_m2;
    string      chemicalName;
    int         spraySessionsDone;
    vector<int> scheduleDays;

    static string modeToString(SprayMode m);

public:
    SprayerBot(const string& id,
               SprayMode mode          = SprayMode::FERTILIZER,
               double    tankCapacityL = 50.0,
               double    sprayRate     =  0.3,
               string    chemical      = "NPK-20-20-20");

    void setMode(SprayMode m)                { mode         = m;    }
    void setChemical(const string& chem)     { chemicalName = chem; }
    void setSchedule(const vector<int>& days){ scheduleDays = days; }
    void refillTank();

    bool sprayArea(double areaSqM);
    bool isScheduledToday(int dayOfWeek) const;

    void performTask()        override;
    void statusReport() const override;

    double getTankLevel() const { return tankLevelL; }
};