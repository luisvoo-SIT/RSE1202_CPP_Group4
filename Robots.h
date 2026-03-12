#pragma once
#include "Plot.h"
#include <string>
#include <iostream>

// =====================================================================
//  Robot base class -- acts towards class (Plot)
//  All display messages use 1-based coordinates (row+1, col+1).
// =====================================================================
class Robot {
public:
    virtual ~Robot() = default;
    virtual bool execute(Plot& plot, int row, int col) = 0;
    virtual std::string typeName() const = 0;
};

// =====================================================================
//  PlantRobot
// =====================================================================
class PlantRobot : public Robot {
public:
    explicit PlantRobot(const std::string& cropName) : cropName_(cropName) {}

    bool execute(Plot& plot, int row, int col) override {
        const Cell& c = plot.getCell(row, col);
        if (c.isPlanted) {
            std::cout << "  [Plant] Row " << (row+1) << ", Col " << (col+1)
                      << " is already occupied by " << c.cropName << ".\n";
            return false;
        }
        bool ok = plot.plantCrop(row, col, cropName_);
        if (ok)
            std::cout << "  [Plant] " << cropName_
                      << " planted at Row " << (row+1) << ", Col " << (col+1) << ".\n";
        else
            std::cout << "  [Plant] Failed at Row " << (row+1)
                      << ", Col " << (col+1) << ".\n";
        return ok;
    }

    std::string typeName() const override { return "PlantRobot"; }
private:
    std::string cropName_;
};

// =====================================================================
//  WaterRobot
//  NOTE: The arrow symbol (->) is used instead of Unicode to avoid
//        garbled text on Windows terminals.
// =====================================================================
class WaterRobot : public Robot {
public:
    bool execute(Plot& plot, int row, int col) override {
        const Cell& before = plot.getCell(row, col);
        if (!before.isPlanted) {
            std::cout << "  [Water] No crop at Row " << (row+1)
                      << ", Col " << (col+1) << ".\n";
            return false;
        }
        if (before.isWithered) {
            std::cout << "  [Water] Crop at Row " << (row+1)
                      << ", Col " << (col+1) << " has withered, cannot water.\n";
            return false;
        }
        int prevLevel = before.waterLevel;
        bool ok = plot.waterCrop(row, col);
        if (ok) {
            const Cell& after = plot.getCell(row, col);
            std::cout << "  [Water] " << after.cropName
                      << " at Row " << (row+1) << ", Col " << (col+1)
                      << "  |  Water: " << prevLevel << "% -> " << after.waterLevel << "%\n";
        }
        return ok;
    }

    std::string typeName() const override { return "WaterRobot"; }
};

// =====================================================================
//  HarvestRobot
// =====================================================================
class HarvestRobot : public Robot {
public:
    bool execute(Plot& plot, int row, int col) override {
        const Cell& c = plot.getCell(row, col);
        if (!c.isPlanted) {
            std::cout << "  [Harvest] No crop at Row " << (row+1)
                      << ", Col " << (col+1) << ".\n";
            return false;
        }
        if (c.isWithered) {
            std::cout << "  [Harvest] " << c.cropName << " at Row " << (row+1)
                      << ", Col " << (col+1) << " has withered.\n";
            return false;
        }
        if (!c.isMature) {
            std::cout << "  [Harvest] " << c.cropName << " at Row " << (row+1)
                      << ", Col " << (col+1) << " is not mature yet.\n";
            return false;
        }
        std::string crop = c.cropName;
        int yield = plot.harvestCrop(row, col);
        if (yield >= 0)
            std::cout << "  [Harvest] " << crop
                      << " at Row " << (row+1) << ", Col " << (col+1)
                      << "  |  Yield: " << yield << " units.\n";
        return yield >= 0;
    }

    std::string typeName() const override { return "HarvestRobot"; }
};
