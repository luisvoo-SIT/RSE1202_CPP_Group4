#pragma once
#include "Cell.h"
#include "CropData.h"
#include "Sensor.h"
#include "History.h"
#include <array>
#include <string>
#include <memory>
#include <iostream>
#include <iomanip>

// =====================================================================
//  Plot  (Class 2)  --  9x9 agricultural grid
//
//  Stores.Crop       : holds data of 9x9 grid
//  Read.Sensor       : receive data from sensors
//  Send.Data         : sends sensor / robot data to UI
//  Receive robot actions
//
//  NOTE: All public methods use 0-based indexing internally.
//        The UI layer converts 1-9 input to 0-8 before calling here.
// =====================================================================
class Plot {
public:
    static constexpr int GRID_SIZE = 9;

    // Active global instance that History reads from
    // (global variable placed within class Plot, per whiteboard)
    static Plot* activeInstance;

    explicit Plot(History& history)
        : currentDay_(1), history_(history)
    {
        sensors_.push_back(std::make_unique<MoistureSensor>());
        sensors_.push_back(std::make_unique<TemperatureSensor>());
        sensors_.push_back(std::make_unique<HumiditySensor>());
        activeInstance = this;
    }

    ~Plot() { if (activeInstance == this) activeInstance = nullptr; }

    // -----------------------------------------------------------------
    //  Stores.Crop : plant a crop at (row, col)
    // -----------------------------------------------------------------
    bool plantCrop(int row, int col, const std::string& cropName) {
        if (!inBounds(row, col)) return false;
        Cell& c = grid_[row][col];
        if (c.isPlanted) return false;
        c.reset();
        c.cropName    = cropName;
        c.plantedDay  = currentDay_;
        c.waterLevel  = 50;
        c.lastWatered = currentDay_;
        c.isPlanted   = true;
        history_.recordPlant(currentDay_, row, col, cropName);
        return true;
    }

    // -----------------------------------------------------------------
    //  Robot action: water a crop
    // -----------------------------------------------------------------
    bool waterCrop(int row, int col) {
        if (!inBounds(row, col)) return false;
        Cell& c = grid_[row][col];
        if (!c.isPlanted || c.isWithered || c.isHarvested) return false;
        const CropData* cd = CropRegistry::instance().find(c.cropName);
        int add = cd ? cd->waterPerSession : 20;
        c.waterLevel  = std::min(100, c.waterLevel + add);
        c.lastWatered = currentDay_;
        c.droughtDays = 0;  // reset drought counter when watered
        history_.recordWater(currentDay_, row, col, c.cropName, c.waterLevel);
        return true;
    }

    // -----------------------------------------------------------------
    //  Robot action: harvest a mature crop
    // -----------------------------------------------------------------
    int harvestCrop(int row, int col) {
        if (!inBounds(row, col)) return -1;
        Cell& c = grid_[row][col];
        if (!c.isPlanted || !c.isMature || c.isWithered || c.isHarvested) return -1;
        const CropData* cd = CropRegistry::instance().find(c.cropName);
        int yield = cd ? cd->harvestYield : 5;
        if (c.waterLevel >= 70) yield = static_cast<int>(yield * 1.2f);
        history_.recordHarvest(currentDay_, row, col, c.cropName, yield);
        c.reset();
        return yield;
    }

    // -----------------------------------------------------------------
    //  Clear a withered cell manually
    // -----------------------------------------------------------------
    bool clearCell(int row, int col) {
        if (!inBounds(row, col)) return false;
        Cell& c = grid_[row][col];
        if (!c.isWithered) return false;
        c.reset();
        return true;
    }

    // -----------------------------------------------------------------
    //  Read.Sensor -- display sensor readings for a cell
    // -----------------------------------------------------------------
    void readSensors(int row, int col) const {
        if (!inBounds(row, col)) return;
        const Cell& c  = grid_[row][col];
        const CropData* cd = c.isPlanted
            ? CropRegistry::instance().find(c.cropName) : nullptr;

        std::cout << "\n";
        std::cout << "  " << std::left
                  << std::setw(16) << "Sensor"
                  << std::setw(12) << "Reading"
                  << std::setw(10) << "Unit"
                  << "Status\n";
        std::cout << "  " << std::string(52, '-') << "\n";

        for (auto& s : sensors_) {
            float val = s->read(c, currentDay_);
            bool  ok  = s->isOptimal(val, cd);
            std::string unit = s->unit();
            if (unit == "degC") unit = "deg C";
            std::cout << "  " << std::left
                      << std::setw(16) << s->name()
                      << std::setw(12) << static_cast<int>(val)
                      << std::setw(10) << unit
                      << (ok ? "OK  -- Optimal" : "WARN -- Suboptimal") << "\n";
        }
        std::cout << "  " << std::string(52, '-') << "\n\n";
        if (!cd)
            std::cout << "  (No crop planted -- optimal ranges not applicable)\n";
    }

    // -----------------------------------------------------------------
    //  Time skip: advance N days with full simulation per day
    // -----------------------------------------------------------------
    void advanceDays(int days) {
        for (int d = 0; d < days; ++d) {
            currentDay_++;
            tickAllCells();
        }
    }

    // -----------------------------------------------------------------
    //  Send.Data getters
    // -----------------------------------------------------------------
    const Cell& getCell(int row, int col) const { return grid_[row][col]; }
    Cell&       getCell(int row, int col)        { return grid_[row][col]; }
    int         getCurrentDay()  const           { return currentDay_; }
    bool        inBounds(int r, int c) const     {
        return r >= 0 && r < GRID_SIZE && c >= 0 && c < GRID_SIZE;
    }

private:
    // -----------------------------------------------------------------
    //  Per-day simulation tick for all cells
    // -----------------------------------------------------------------
    void tickAllCells() {
        for (int r = 0; r < GRID_SIZE; r++) {
            for (int c = 0; c < GRID_SIZE; c++) {
                Cell& cell = grid_[r][c];
                if (!cell.isPlanted || cell.isWithered) continue;

                // Drain water each day
                cell.waterLevel = std::max(0, cell.waterLevel - 10);

                // Track consecutive drought days
                if (cell.waterLevel == 0) {
                    cell.droughtDays++;
                } else {
                    cell.droughtDays = 0;
                }

                // Wither if drought lasts 3+ consecutive days
                if (cell.droughtDays >= 3) {
                    cell.isWithered = true;
                    cell.isMature   = false;
                    continue; // skip maturity check
                }

                // Check maturity (only if healthy and watered)
                const CropData* cd = CropRegistry::instance().find(cell.cropName);
                if (cd && !cell.isMature) {
                    int age = currentDay_ - cell.plantedDay;
                    if (age >= cd->growthDays) cell.isMature = true;
                }
            }
        }
    }

    int                                                 currentDay_;
    std::array<std::array<Cell, GRID_SIZE>, GRID_SIZE>  grid_;
    std::vector<std::unique_ptr<Sensor>>                sensors_;
    History&                                            history_;
};

inline Plot* Plot::activeInstance = nullptr;
