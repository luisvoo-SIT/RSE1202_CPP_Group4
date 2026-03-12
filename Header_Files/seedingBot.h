#pragma once
#include "Robots.h"
#include "CropsV2.h"
#include <string>

using namespace std;

using namespace std;

class SeedingBot : public Robot {
private:
    Crop assignedCrop;
    int  seedsPlanted;

public:
    SeedingBot(const string& id, const Crop& crop);

    void setCrop(const Crop& crop) { assignedCrop = crop; }

    string getCropName()    const { return assignedCrop.getName();            }
    int    getTimeToGrow()  const { return assignedCrop.getTimeToGrow();      }
    int    getWaterNeeded() const { return assignedCrop.getWaterRequirements(); }

    void plantSeeds(int count);

    void performTask()        override;
    void statusReport() const override;

    int getSeedsPlanted() const { return seedsPlanted; }
};