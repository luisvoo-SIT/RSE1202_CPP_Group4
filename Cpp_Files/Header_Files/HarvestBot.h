#pragma once
#include "Robots.h"
#include <string>
#include <vector>

using namespace std;

class HarvestingBot : public Robot {
public:
    static constexpr double DEFAULT_RIPENESS_THRESHOLD = 75.0;

private:
    struct HarvestRecord {
        string cropType;
        double ripenessScore;
        double yieldKg;
    };

    string              cropType;
    double              ripenessThreshold;
    double              binCapacityKg;
    double              binCurrentKg;
    int                 harvests;
    vector<HarvestRecord> log;

    double senseRipeness(const string& zone) const;

public:
    HarvestingBot(const string& id,
                  const string& cropType,
                  double binCapacityKg     = 200.0,
                  double ripenessThreshold = DEFAULT_RIPENESS_THRESHOLD);

    void setCropType(const string& crop) { cropType          = crop; }
    void setRipenessThreshold(double t)  { ripenessThreshold = t;    }

    bool   evaluateAndHarvest(const string& zone, double expectedYieldKg);
    double emptyBin();

    void performTask()        override;
    void statusReport() const override;

    double getBinLevel() const { return binCurrentKg; }
    int    getHarvests() const { return harvests;     }
};