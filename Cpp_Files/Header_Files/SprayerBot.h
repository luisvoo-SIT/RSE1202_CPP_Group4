#pragma once
#include "Robots.h"
#include <string>

using namespace std;

class SprayerBot : public Robot {
public:
    enum class SprayMode { FERTILIZER, PESTICIDE, HERBICIDE };

private:
    SprayMode   mode;
    double      tankCapacityL;
    double      tankLevelL;
    double      sprayRateL_per_m2;
    string chemicalName;
    int         spraySessionsDone;

    static string modeToString(SprayMode m);

public:
    SprayerBot(const string& id,
               double             tankCapacityL,
               double             sprayRate);

    bool sprayArea(double areaSqM);     // ← user prompted inside
    void statusReport() const;

    SprayMode   getMode()          const { return mode;             }
    double      getTankLevel()     const { return tankLevelL;       }
    double      getTankCapacity()  const { return tankCapacityL;    }
    int         getSpraySessions() const { return spraySessionsDone;}
    string getChemicalName()  const { return chemicalName;     }
};