#pragma once
#include "Robots.h"
#include "CropsV2.h"
#include <string>
#include <vector>

using namespace std;

class SeedingBot : public Robot {
private:
    CropData assignedCrop;
    int  seedsPlanted;
    vector<CropData>   seedLog;   

public:
    SeedingBot(const string& id, const CropData& crop);

    void   setCrop(const CropData& crop) { assignedCrop = crop; }

    CropData plantSeeds(int count, const vector<CropData>& crops);
    void   statusReport() const;

    string getCropName()     const { return assignedCrop.getName();             }
    int    getTimeToGrow()   const { return assignedCrop.getTimeToGrow();       }
    int    getWaterNeeded()  const { return assignedCrop.getWaterReq(); }
    int    getSeedsPlanted() const { return seedsPlanted;                       }
};
