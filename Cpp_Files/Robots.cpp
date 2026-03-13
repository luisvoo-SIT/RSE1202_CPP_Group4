#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>

#include "Header_Files/Robots.h"
#include "Header_Files/seedingBot.h"
#include "Header_Files/SprayerBot.h"
#include "Header_Files/CropsV2.h"
#include "Header_Files/HarvestBot.h"

using namespace std;
/*
Start of Parent class: Robot
Initialises global variables that the child classes will need
Provides user with information in the status of the robot
*/

Robot::Robot(const string& id, const string& name)
    : id(id), name(name), batteryLevel(100.0), isOperational(true) {}
Robot:: ~Robot(){}    

void Robot::consumeBattery(double amount) {
    batteryLevel -= amount;
    if (batteryLevel <= 0.0) {
        batteryLevel  = 0.0;
        isOperational = false;
        cout << name << " battery depleted – shutting down.\n";
    }
}

void Robot::recharge() {
    batteryLevel = 100.0;
    cout << name << " fully recharged.\n";
}

void Robot::shutdown() {
    isOperational = false;
    cout << name << " shut down.\n";
}

void Robot::statusReport() const {
    cout << "=== " << name << " [" << id << "] ===\n"
         << "  Battery    : " << batteryLevel << "%\n"
         << "  Operational: " << (isOperational ? "Yes" : "No") << "\n";
}         

/*
Start of Child Class: SeedingBot
Purpose: so that the user can plant crops in to the plot.
Gets data from Crops.cpp, and places it into Plot.cpp
Provides report at the end 
*/

SeedingBot::SeedingBot(const string& id, const Crop& crop)
    : Robot(id, "SeedingBot-" + id),
      assignedCrop(crop),
      seedsPlanted(0) {}

void SeedingBot::plantSeeds(int count) {
    if (!isOperational) {
        cout << name << " is not operational.\n";
        return;
    }

    cout << name << ": Planting " << count
         << " " << assignedCrop.getName() << " seeds\n"
         << "  Time to Grow : " << assignedCrop.getTimetoGrow()       << " days\n"
         << "  Water/day    : " << assignedCrop.getwaterRequirements() << " mL\n";

    seedsPlanted += count;
    consumeBattery(count * 0.05);

    cout << "  Done. Total seeds planted: " << seedsPlanted << "\n";
}

void SeedingBot::performTask() {
    cout << name << ": Running standard seeding task...\n";
    plantSeeds(0);
}

void SeedingBot::statusReport() const {
    Robot::statusReport();
    
    cout << "  Crop         : " <<getName()             << "\n"
         << "  Time to Grow : " << assignedCrop.getTimetoGrow()       << " days\n"
         << "  Humidity     : " << assignedCrop.getminHumidity()
                                << " - " << assignedCrop.getmaxHumidity()    << " %\n"
         << "  Temperature  : " << assignedCrop.getminTemperature()
                                << " - " << assignedCrop.getmaxTemperature() << " C\n"
         << "  UV Intensity : " << assignedCrop.getminUVIntensity()
                                << " - " << assignedCrop.getmaxUVIntensity() << "\n"
         << "  Water/day    : " << assignedCrop.getwaterRequirements() << " mL\n"
         << "  Seeds Planted: " << seedsPlanted                       << "\n";
}

/*
Start of Child Class: SprayerBot 
Purpose: spray different agents on plants, based on user's choice 
Provides report at the end 
*/

string SprayerBot::modeToString(SprayMode m) {
    switch (m) {
        case SprayMode::FERTILIZER: return "Fertilizer";
        case SprayMode::PESTICIDE:  return "Pesticide";
        case SprayMode::HERBICIDE:  return "Herbicide";
        case SprayMode::CUSTOM:     return "Custom";
    }
    return "Unknown";
}

SprayerBot::SprayerBot(const string& id,
                       SprayMode mode,
                       double    tankCapacityL,
                       double    sprayRate,
                       string    chemical)
    : Robot(id, "SprayerBot-" + id),
      mode(mode),
      tankCapacityL(tankCapacityL),
      tankLevelL(tankCapacityL),
      sprayRateL_per_m2(sprayRate),
      chemicalName(std::move(chemical)),
      spraySessionsDone(0) {}

void SprayerBot::refillTank() {
    tankLevelL = tankCapacityL;
    cout << name << " tank refilled to " << tankCapacityL << " L.\n";
}

bool SprayerBot::sprayArea(double areaSqM) {
    if (!isOperational) { cout << name << " is not operational.\n"; return false; }
    double required = areaSqM * sprayRateL_per_m2;
    if (required > tankLevelL) {
        cout << name << ": Insufficient chemical – need " << required
             << " L, have " << tankLevelL << " L. Refill required.\n";
        return false;
    }
    cout << name << ": Spraying " << areaSqM << " m² with "
         << chemicalName << " [" << modeToString(mode) << "]...\n";
    tankLevelL -= required;
    consumeBattery(areaSqM * 0.02);
    ++spraySessionsDone;
    cout << "  Used " << required << " L | Tank remaining: " << tankLevelL << " L\n";
    return true;
}

bool SprayerBot::isScheduledToday(int dayOfWeek) const {
    for (int d : scheduleDays)
        if (d == dayOfWeek) return true;
    return false;
}

void SprayerBot::performTask() {
    sprayArea(200.0);
}

void SprayerBot::statusReport() const {
    Robot::statusReport();
    cout << "  Mode       : " << modeToString(mode) << "\n"
         << "  Chemical   : " << chemicalName        << "\n"
         << "  Tank       : " << tankLevelL << " / " << tankCapacityL << " L\n"
         << "  Spray Rate : " << sprayRateL_per_m2  << " L/m²\n"
         << "  Sessions   : " << spraySessionsDone   << "\n";
}

/*
Start of Child Class: HarvestBot
Purpose: to harvest crops from Plots 
produces report at the end 
*/


HarvestingBot::HarvestingBot(const string& id,
                             const string& cropType,
                             double binCapacityKg,
                             double ripenessThreshold)
    : Robot(id, "HarvestingBot-" + id),
      cropType(cropType),
      ripenessThreshold(ripenessThreshold),
      binCapacityKg(binCapacityKg),
      binCurrentKg(0.0),
      harvests(0) {}

double HarvestingBot::senseRipeness(const string& zone) const {
    return 60.0 + (zone.size() % 4) * 10.0;
}

bool HarvestingBot::evaluateAndHarvest(const string& zone, double expectedYieldKg) {
    if (!isOperational) { cout << name << " is not operational.\n"; return false; }

    double ripeness = senseRipeness(zone);
    cout << name << ": Scanning zone [" << zone << "] – ripeness score: "
         << ripeness << "/100 (threshold " << ripenessThreshold << ")\n";

    if (ripeness < ripenessThreshold) {
        cout << "  Crop not yet ripe. Skipping.\n";
        return false;
    }
    if (binCurrentKg + expectedYieldKg > binCapacityKg) {
        cout << "  Bin full! Empty bin before continuing.\n";
        return false;
    }

    cout << "  Harvesting " << expectedYieldKg << " kg of " << cropType << "...\n";
    binCurrentKg += expectedYieldKg;
    consumeBattery(expectedYieldKg * 0.08);
    log.push_back({cropType, ripeness, expectedYieldKg});
    ++harvests;
    cout << "  Bin: " << binCurrentKg << " / " << binCapacityKg << " kg\n";
    return true;
}

double HarvestingBot::emptyBin() {
    double collected = binCurrentKg;
    binCurrentKg = 0.0;
    cout << name << ": Bin emptied – " << collected << " kg transferred.\n";
    return collected;
}

void HarvestingBot::performTask() {
    evaluateAndHarvest("Field-A1", 50.0);
}

void HarvestingBot::statusReport() const {
    Robot::statusReport();
    cout << "  Crop Type  : " << cropType          << "\n"
         << "  Ripeness ≥ : " << ripenessThreshold  << "/100\n"
         << "  Bin        : " << binCurrentKg << " / " << binCapacityKg << " kg\n"
         << "  Harvests   : " << harvests            << "\n";
    if (!log.empty()) {
        cout << "  Harvest Log:\n";
        for (const auto& r : log)
            cout << "    " << r.cropType << " | ripeness " << r.ripenessScore
                 << " | " << r.yieldKg << " kg\n";
    }
}

int main() {
    cout << "========================================\n"
         << "      HarvestingBot Test Program\n"
         << "========================================\n\n";

    // ── Step 1: Load crops from CSV ───────────────────────────
    vector<Crop> crops = Crop::loadCrops("Crop_Info.csv");

    if (crops.empty()) {
        cout << "No crops loaded. Check your CSV file.\n";
        return 1;
    }

    // ── Step 2: Display available crops ──────────────────────
    cout << "=== Available Crops ===\n";
    for (size_t i = 0; i < crops.size(); ++i) {
        cout << i + 1 << ". " << crops[i].getName() << "\n";
    }

    // ── Step 3: Select a crop ─────────────────────────────────
    int choice;
    cout << "\nSelect a crop number to harvest: ";
    cin  >> choice;

    if (choice < 1 || choice > (int)crops.size()) {
        cout << "Invalid choice.\n";
        return 1;
    }

    Crop selectedCrop = crops[choice - 1];

    // ── Step 4: Create HarvestingBot ──────────────────────────
    double binCapacity        = 300.0;
    double ripenessThreshold  = 70.0;

    HarvestingBot harvester("H01", selectedCrop.getName(),
                             binCapacity, ripenessThreshold);

    cout << "\n========================================\n"
         << "         Initial Status Report\n"
         << "========================================\n";
    harvester.statusReport();

    // ── Test 1: Harvest a zone that is NOT ripe ───────────────
    cout << "\n========================================\n"
         << "   Test 1: Harvest Unripe Zone\n"
         << "========================================\n";
    harvester.evaluateAndHarvest("Field-A1", 50.0);

    // ── Test 2: Harvest zones that ARE ripe ───────────────────
    cout << "\n========================================\n"
         << "   Test 2: Harvest Ripe Zones\n"
         << "========================================\n";
    harvester.evaluateAndHarvest("Zone-1", 60.0);
    harvester.evaluateAndHarvest("Zone-2", 80.0);
    harvester.evaluateAndHarvest("Zone-3", 70.0);

    // ── Status after harvesting ───────────────────────────────
    cout << "\n========================================\n"
         << "      Status After Harvesting\n"
         << "========================================\n";
    harvester.statusReport();

    // ── Test 3: Fill the bin to capacity ─────────────────────
    cout << "\n========================================\n"
         << "   Test 3: Fill Bin to Capacity\n"
         << "========================================\n";
    harvester.evaluateAndHarvest("Zone-4", 90.0);
    harvester.evaluateAndHarvest("Zone-5", 90.0);
    harvester.evaluateAndHarvest("Zone-6", 90.0);   // should trigger bin full warning

    // ── Test 4: Empty the bin ─────────────────────────────────
    cout << "\n========================================\n"
         << "         Test 4: Empty Bin\n"
         << "========================================\n";
    double collected = harvester.emptyBin();
    cout << "Total collected and transferred: " << collected << " kg\n";

    // ── Test 5: Harvest again after emptying bin ──────────────
    cout << "\n========================================\n"
         << "   Test 5: Harvest After Emptying Bin\n"
         << "========================================\n";
    harvester.evaluateAndHarvest("Zone-1", 50.0);

    // ── Test 6: Drain battery completely ─────────────────────
    cout << "\n========================================\n"
         << "      Test 6: Drain Battery\n"
         << "========================================\n";
    cout << "Draining battery with large harvests...\n";
    for (int i = 0; i < 10; ++i) {
        harvester.emptyBin();
        harvester.evaluateAndHarvest("Zone-1", 100.0);
    }

    // ── Test 7: Try harvesting when offline ──────────────────
    cout << "\n========================================\n"
         << "   Test 7: Harvest When Offline\n"
         << "========================================\n";
    harvester.evaluateAndHarvest("Zone-1", 50.0);   // should say not operational

    // ── Test 8: Recharge and try again ───────────────────────
    cout << "\n========================================\n"
         << "      Test 8: Recharge and Retry\n"
         << "========================================\n";
    harvester.recharge();
    harvester.emptyBin();
    harvester.evaluateAndHarvest("Zone-1", 50.0);

    // ── Final status report ───────────────────────────────────
    cout << "\n========================================\n"
         << "         Final Status Report\n"
         << "========================================\n";
    harvester.statusReport();

    cout << "\n========================================\n"
         << "         All Tests Complete\n"
         << "========================================\n";

    return 0;
}