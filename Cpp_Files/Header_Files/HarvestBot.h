#pragma once
#include "Robots.h"
#include "plotv2.h"
#include "CropsV2.h"
#include "seedingBot.h"
#include <string>
#include <vector>

class HarvestingBot : public Robot {
private:
    struct HarvestRecord {
        std::string      cropName;
        Plot::Status status;
        double           yieldKg;
    };

    double                     totalHarvestedKg;
    double                     totalDeadKg;
    double                     totalPlantKg;
    int                        harvests;
    std::vector<HarvestRecord> log;

    static std::string statusToString(Plot::Status status);

public:
    HarvestingBot(const std::string& id);

    bool evaluateAndHarvest(const CropData   farm[3][3],
                            int              r,
                            int              c,
                            Plot::Status status);

    void statusReport() const;

    double getTotalHarvested() const { return totalHarvestedKg; }
    double getTotalDead()      const { return totalDeadKg;       }
    double getTotalPlant()     const { return totalPlantKg;      }
    int    getHarvests()       const { return harvests;           }
};