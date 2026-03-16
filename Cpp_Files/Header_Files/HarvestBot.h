#pragma once
#include "Robots.h"
#include <string>
#include <vector>

using namespace std;

class HarvestingBot : public Robot {
public:
    enum class PlantStatus { SEED, PLANT, DEAD };

private:
    struct HarvestRecord {
        string      cropType;
        PlantStatus status;
        double      yieldKg;
    };

    string                cropType;
    double                totalHarvestedKg;
    double                totalDeadKg;
    double                totalPlantKg;
    int                   harvests;
    vector<HarvestRecord> log;

    static string statusToString(PlantStatus status);

public:
    HarvestingBot(const string& id, const string& cropType);

    void setCropType(const string& crop) { cropType = crop; }

    bool evaluateAndHarvest(const string& zone,
                            double        expectedYieldKg,
                            PlantStatus   status);
    void statusReport() const;

    double getTotalHarvested() const { return totalHarvestedKg; }
    double getTotalDead()      const { return totalDeadKg;       }
    double getTotalPlant()     const { return totalPlantKg;      }
    int    getHarvests()       const { return harvests;           }
};