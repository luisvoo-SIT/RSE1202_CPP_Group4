#pragma once
#include "Robots.h"
#include "CropsV2.h"
#include <string>
#include <vector>

using namespace std;

class SeedingBot : public Robot {
private:
    Crop assignedCrop;
    int  seedsPlanted;

public:
    SeedingBot(const string& id, const Crop& crop);

    void   setCrop(const Crop& crop) { assignedCrop = crop; }

    string plantSeeds(int count, const vector<Crop>& crops);
    void   statusReport() const;

    string getCropName()     const { return assignedCrop.getName();             }
    int    getTimeToGrow()   const { return assignedCrop.getTimetoGrow();       }
    int    getWaterNeeded()  const { return assignedCrop.getwaterRequirements(); }
    int    getSeedsPlanted() const { return seedsPlanted;                       }
};
