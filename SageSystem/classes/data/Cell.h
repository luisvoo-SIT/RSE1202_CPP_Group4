#pragma once
#include <string>

// =====================================================================
//  Cell -- one tile in the 9x9 Plot grid
// =====================================================================
struct Cell {
    std::string cropName;
    int  plantedDay   = 0;   // game day crop was planted
    int  waterLevel   = 0;   // 0-100, drains 10 per day
    int  lastWatered  = 0;   // last day it was watered
    int  droughtDays  = 0;   // consecutive days at water level 0
    bool isPlanted    = false;
    bool isMature     = false;
    bool isWithered   = false; // true when drought killed the crop
    bool isHarvested  = false;

    void reset() {
        cropName    = "";
        plantedDay  = 0;
        waterLevel  = 0;
        lastWatered = 0;
        droughtDays = 0;
        isPlanted   = false;
        isMature    = false;
        isWithered  = false;
        isHarvested = false;
    }
};
