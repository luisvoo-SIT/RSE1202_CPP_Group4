#include "Header_Files/Robots.h"
#include "Header_Files/seedingBot.h"
#include "Header_Files/SprayerBot.h"
#include "Header_Files/HarvestBot.h"
#include <iostream>

using namespace std;

// ══════════════════════════════════════════════════════════════
//  ROBOT BASE CLASS
// ══════════════════════════════════════════════════════════════

Robot::Robot(const string& id, const string& name)
    : id(id), name(name) {}

void Robot::statusReport() const {
    cout << "=== " << name << " [" << id << "] ===\n";
}

// ══════════════════════════════════════════════════════════════
//  SEEDING BOT
// ══════════════════════════════════════════════════════════════

SeedingBot::SeedingBot(const string& id, const Crop& crop)
    : Robot(id, "SeedingBot-" + id),
      assignedCrop(crop),
      seedsPlanted(0) {}

string SeedingBot::plantSeeds(int count, const vector<Crop>& crops) {
    if (crops.empty()) {
        cout << "No crops available.\n";
        return "";
    }

    // ── User selects seed type ────────────────────────────────
    cout << "\n=== Available Seed Types ===\n";
    for (size_t i = 0; i < crops.size(); ++i)
        cout << i + 1 << ". " << crops[i].getName() << "\n";

    int choice;
    cout << "\nSelect a seed type: ";
    cin  >> choice;

    if (choice < 1 || choice > (int)crops.size()) {
        cout << "Invalid choice.\n";
        return "";
    }

    assignedCrop  = crops[choice - 1];
    seedsPlanted += count;

    cout << name << ": Planting " << count
         << " " << assignedCrop.getName()                              << " seeds\n"
         << "  Time to Grow : " << assignedCrop.getTimetoGrow()        << " days\n"
         << "  Water/day    : " << assignedCrop.getwaterRequirements() << " mL\n"
         << "  Total Planted: " << seedsPlanted                        << "\n";

    return assignedCrop.getName();
}

void SeedingBot::statusReport() const {
    Robot::statusReport();
    cout << "  Crop         : " << assignedCrop.getName()               << "\n"
         << "  Time to Grow : " << assignedCrop.getTimetoGrow()         << " days\n"
         << "  Humidity     : " << assignedCrop.getminHumidity()
                                << " - " << assignedCrop.getmaxHumidity()    << " %\n"
         << "  Temperature  : " << assignedCrop.getminTemperature()
                                << " - " << assignedCrop.getmaxTemperature() << " C\n"
         << "  UV Intensity : " << assignedCrop.getminUVIntensity()
                                << " - " << assignedCrop.getmaxUVIntensity() << "\n"
         << "  Water/day    : " << assignedCrop.getwaterRequirements()  << " mL\n"
         << "  Seeds Planted: " << seedsPlanted                         << "\n";
}

// ══════════════════════════════════════════════════════════════
//  SPRAYER BOT
// ══════════════════════════════════════════════════════════════

string SprayerBot::modeToString(SprayMode m) {
    switch (m) {
        case SprayMode::FERTILIZER: return "Fertilizer";
        case SprayMode::PESTICIDE:  return "Pesticide";
        case SprayMode::HERBICIDE:  return "Herbicide";
    }
    return "Unknown";
}

SprayerBot::SprayerBot(const string& id,
                       SprayMode     mode,
                       double        tankCapacityL,
                       double        sprayRate,
                       string        chemicalName)
    : Robot(id, "SprayerBot-" + id),
      mode(mode),
      tankCapacityL(tankCapacityL),
      tankLevelL(tankCapacityL),
      sprayRateL_per_m2(sprayRate),
      chemicalName(std::move(chemicalName)),
      spraySessionsDone(0) {}

bool SprayerBot::sprayArea(double areaSqM) {
    double required = areaSqM * sprayRateL_per_m2;

    if (tankLevelL < required) {
        cout << name << ": Not enough chemical. Need "
             << required << " L, have " << tankLevelL << " L\n";
        return false;
    }

    tankLevelL -= required;
    ++spraySessionsDone;

    cout << name << ": Spraying " << areaSqM << " m² with "
         << chemicalName          << " (" << modeToString(mode) << ")\n"
         << "  Used     : "       << required   << " L\n"
         << "  Remaining: "       << tankLevelL << " L\n";

    return true;
}

void SprayerBot::refillTank() {
    tankLevelL = tankCapacityL;
    cout << name << ": Tank refilled to " << tankCapacityL << " L\n";
}

void SprayerBot::statusReport() const {
    Robot::statusReport();
    cout << "  Mode         : " << modeToString(mode) << "\n"
         << "  Chemical     : " << chemicalName        << "\n"
         << "  Tank         : " << tankLevelL
                                << " / " << tankCapacityL << " L\n"
         << "  Spray Rate   : " << sprayRateL_per_m2  << " L/m²\n"
         << "  Sessions Done: " << spraySessionsDone   << "\n";
}

// ══════════════════════════════════════════════════════════════
//  HARVESTING BOT
// ══════════════════════════════════════════════════════════════

string HarvestingBot::statusToString(PlantStatus status) {
    switch (status) {
        case PlantStatus::SEED:  return "Seed";
        case PlantStatus::PLANT: return "Plant";
        case PlantStatus::DEAD:  return "Dead";
    }
    return "Unknown";
}

HarvestingBot::HarvestingBot(const string& id, const string& cropType)
    : Robot(id, "HarvestingBot-" + id),
      cropType(cropType),
      totalHarvestedKg(0.0),
      totalDeadKg(0.0),
      totalPlantKg(0.0),
      harvests(0) {}

bool HarvestingBot::evaluateAndHarvest(const string& zone,
                                       double        expectedYieldKg,
                                       PlantStatus   status) {
    cout << name << ": Scanning zone [" << zone << "]\n"
         << "  Plant Status : " << statusToString(status) << "\n";

    switch (status) {
        case PlantStatus::SEED:
            cout << "  Seed detected – too early to harvest. Skipping.\n";
            return false;

        case PlantStatus::PLANT:
            cout << "  Plant ready – harvesting " << expectedYieldKg
                 << " kg of " << cropType << "...\n";
            totalPlantKg     += expectedYieldKg;
            totalHarvestedKg += expectedYieldKg;
            log.push_back({cropType, status, expectedYieldKg});
            ++harvests;
            cout << "  Plant harvested : " << totalPlantKg     << " kg\n"
                 << "  Total harvested : " << totalHarvestedKg << " kg\n";
            return true;

        case PlantStatus::DEAD:
            cout << "  Dead crop – collecting "
                 << expectedYieldKg * 0.5
                 << " kg of " << cropType << "...\n";
            totalDeadKg      += expectedYieldKg * 0.5;
            totalHarvestedKg += expectedYieldKg * 0.5;
            log.push_back({cropType, status, expectedYieldKg * 0.5});
            ++harvests;
            cout << "  Dead collected  : " << totalDeadKg      << " kg\n"
                 << "  Total harvested : " << totalHarvestedKg << " kg\n";
            return true;
    }
    return false;
}

void HarvestingBot::statusReport() const {
    Robot::statusReport();
    cout << "  Crop Type      : " << cropType        << "\n"
         << "  Harvests Done  : " << harvests         << "\n"
         << "  Total Harvested: " << totalHarvestedKg << " kg\n"
         << "    Plant        : " << totalPlantKg     << " kg\n"
         << "    Dead         : " << totalDeadKg      << " kg\n";

    if (!log.empty()) {
        cout << "  Harvest Log:\n";
        for (const auto& r : log)
            cout << "    " << r.cropType << " | ripeness " << r.ripenessScore
                 << " | " << r.yieldKg << " kg\n";
    }
}

