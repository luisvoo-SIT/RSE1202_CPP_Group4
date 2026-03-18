#pragma once
#include "Robots.h"
#include <string>
#include <vector>

using namespace std;

class SprayerBot : public Robot {
public:
    enum class SprayMode { FERTILIZER, PESTICIDE, HERBICIDE };

private:

    struct SprayRecord {
        string mode;
        string chemicalName;
        double areaSprayed;
        double chemicalUsed;
    };

    SprayMode   mode;
    double      tankCapacityL;
    double      tankLevelL;
    double      sprayRateL_per_m2;
    string chemicalName;
    int         spraySessionsDone;
    vector<SprayRecord> sprayLog;

    static string modeToString(SprayMode m);

public:
    SprayerBot(const string& id,
               double             tankCapacityL,
               double             sprayRate);

    string sprayArea(double areaSqM);  // ← returns string
    void        statusReport() const;

    SprayMode   getMode()          const { return mode;             }
    double      getTankLevel()     const { return tankLevelL;       }
    double      getTankCapacity()  const { return tankCapacityL;    }
    int         getSpraySessions() const { return spraySessionsDone;}
    string      getChemicalName()  const { return chemicalName;     }
    const vector<SprayRecord>& getSprayLog() const { return sprayLog; }
};