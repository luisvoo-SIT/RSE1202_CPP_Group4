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

    void setCrop(const Crop& crop) { assignedCrop; }



    void plantSeeds(int count);

    void performTask()        override;
    void statusReport() const override;

    int getSeedsPlanted() const { return seedsPlanted; }
};