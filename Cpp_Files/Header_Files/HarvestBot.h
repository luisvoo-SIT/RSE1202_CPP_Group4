#pragma once
#include "Robots.h"
#include "plotv2.h"
#include "CropsV2.h"
#include "seedingBot.h"
#include <string>
#include <vector>

class HarvestingBot : public Robot {
public:
    struct HarvestRecord {
        std::string      cropName;
        Plot::Status status;
        double           yieldKg;
    };

private:
    double                     totalHarvestedKg;
    double                     totalDeadKg;
    double                     totalPlantKg;
    int                        harvests;
    std::vector<HarvestRecord> log;

    static std::string statusToString(Plot::Status status);

public:
    HarvestingBot(const std::string& id);

    bool evaluateAndHarvest(const CropData&  cropData,
                            Plot::Status status);

    void statusReport() const;

    double getTotalHarvested()               const { return totalHarvestedKg; }
    double getTotalDead()                    const { return totalDeadKg;       }
    double getTotalPlant()                   const { return totalPlantKg;      }
    int    getHarvests()                     const { return harvests;           }
    const std::vector<HarvestRecord>& getLog() const { return log;             }
};