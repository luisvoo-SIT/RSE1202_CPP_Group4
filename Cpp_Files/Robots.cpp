#include "Header_Files/Robots.h"
#include "Header_Files/seedingBot.h"
#include "Header_Files/SprayerBot.h"
#include "Header_Files/HarvestBot.h"
#include "Header_Files/CropsV2.h"
#include "Header_Files/plotv2.h"

#include <iostream>
#include <random>

using namespace std;

// ══════════════════════════════════════════════════════════════
//  ROBOT BASE CLASS
// ══════════════════════════════════════════════════════════════

Robot::Robot(const string& id, const string& name)
    : id(id), name(name) {}

void Robot::statusReport() const {
   std::cout << "=== " << name << " [" << id << "] ===\n";
}

// ══════════════════════════════════════════════════════════════
//  SEEDING BOT
// ══════════════════════════════════════════════════════════════

SeedingBot::SeedingBot(const string& id, const CropData& crop)
    : Robot(id, "SeedingBot-" + id),
      assignedCrop(crop),
      seedsPlanted(0) {}

CropData SeedingBot::plantSeeds(int count, const vector<CropData>& crops) {
    if (crops.empty()) {
        std::cout << "No crops available.\n";
        return assignedCrop;
    }

    // ── User selects seed type ────────────────────────────────
    std::cout << "\n=== Available Seed Types ===\n";
    for (size_t i = 0; i < crops.size(); ++i)
        std::cout << i + 1 << ". " << crops[i].getName() << "\n";

    int choice;
    std::cout << "\nSelect a seed type: ";
    cin  >> choice;

    if (choice < 1 || choice > (int)crops.size()) {
        std::cout << "Invalid choice.\n";
        return assignedCrop;
    }
    
    assignedCrop  = crops[choice - 1];
    seedsPlanted += count;

    std::cout << name << ": Planting " << count
         << " " << assignedCrop.getName()                              << " seeds\n"
         << "  Time to Grow : " << assignedCrop.getTimeToGrow()<< " days\n"
         << "  Water/day    : " << assignedCrop.getWaterReq() << " mL\n"
         << "  Total Planted: " << seedsPlanted                        << "\n";
    
     
    return assignedCrop;
}

/*
This is the how to impliment the code


CropData plant = seeder.plantSeeds(1, crops);  to store the returned object into the array
farm[r][c] = plant
// ── Access all crop data through the returned object ──────────
cout << "\n=== Selected Crop Data ===\n"
     << "  Crop         : " << farm[r][c].getName()             << "\n"
     << "  Time to Grow : " << farm[r][c].getTimeToGrow()       << " days\n"
     << "  Water/day    : " << farm[r][c].getWaterReq()<< " mL\n"
     << "  Humidity     : " << farm[r][c].getMinHum()
                            << " - " << farm[r][c].getMaxHum() << " %\n"
     << "  Temperature  : " << farm[r][c].getMinTemp()
                            << " - " << farm[r][c].getMaxTemp() << " C\n"
     << "  UV Intensity : " << farm[r][c].getMinUV()
                            << " - " << farm[r][c].getMaxUV() << "\n";
*/


void SeedingBot::statusReport() const {
    Robot::statusReport();
    std::cout << "  Crop         : " << assignedCrop.getName()               << "\n"
         << "  Time to Grow : " << assignedCrop.getTimeToGrow()         << " days\n"
         << "  Humidity     : " << assignedCrop.getMinHum()
                                << " - " << assignedCrop.getMaxHum()    << " %\n"
         << "  Temperature  : " << assignedCrop.getMinTemp()
                                << " - " << assignedCrop.getMaxTemp() << " C\n"
         << "  UV Intensity : " << assignedCrop.getMinUV()
                                << " - " << assignedCrop.getMaxUV()<< "\n"
         << "  Water/day    : " << assignedCrop.getWaterReq()  << " mL\n"
         << "  Seeds Planted: " << seedsPlanted                         << "\n";
}

// ══════════════════════════════════════════════════════════════
//  SPRAYER BOT
// ══════════════════════════════════════════════════════════════

std::string SprayerBot::modeToString(SprayMode m) {
    switch (m) {
        case SprayMode::FERTILIZER: return "Fertilizer";
        case SprayMode::PESTICIDE:  return "Pesticide";
        case SprayMode::HERBICIDE:  return "Herbicide";
    }
    return "Unknown";
}

SprayerBot::SprayerBot(const std::string& id,
                       double             tankCapacityL,
                       double             sprayRate)
    : Robot(id, "SprayerBot-" + id),
      mode(SprayMode::FERTILIZER),     // ← default mode
      tankCapacityL(tankCapacityL),
      tankLevelL(tankCapacityL),
      sprayRateL_per_m2(sprayRate),
      chemicalName(""),
      spraySessionsDone(0) {}

bool SprayerBot::sprayArea(double areaSqM) {
    // ── Step 1: User selects spray mode ──────────────────────
    std::cout << "\n=== Select Spray Mode ===\n"
              << "1. Fertilizer\n"
              << "2. Pesticide\n"
              << "3. Herbicide\n"
              << "Select mode: ";

    int modeChoice;
    std::cin >> modeChoice;

    switch (modeChoice) {
        case 1:
            mode         = SprayMode::FERTILIZER;
            chemicalName = "NitrogenFert";
            break;
        case 2:
            mode         = SprayMode::PESTICIDE;
            chemicalName = "PesticideX";
            break;
        case 3:
            mode         = SprayMode::HERBICIDE;
            chemicalName = "HerbicideY";
            break;
        default:
            std::cout << "Invalid choice. Using current mode: "
                      << modeToString(mode) << "\n";
            break;
    }

    // ── Step 2: User can enter custom chemical name ───────────
    std::cout << "Default chemical: " << chemicalName << "\n"
              << "Use custom chemical name? (y/n): ";
    char custom;
    std::cin >> custom;

    if (custom == 'y' || custom == 'Y') {
        std::cout << "Enter chemical name: ";
        std::cin  >> chemicalName;
    }

    // ── Step 3: Check if tank needs refilling ─────────────────
    double required = areaSqM * sprayRateL_per_m2;

    if (tankLevelL < required) {
        std::cout << "\n  Tank too low to spray.\n"
                  << "  Required : " << required   << " L\n"
                  << "  Available: " << tankLevelL << " L\n"
                  << "  Refill tank? (y/n): ";

        char refill;
        std::cin >> refill;

        if (refill == 'y' || refill == 'Y') {
            tankLevelL = tankCapacityL;
            std::cout << "  Tank refilled to " << tankCapacityL << " L\n";
        } else {
            std::cout << "  Spraying cancelled.\n";
            return false;
        }
    }

    // ── Step 4: Spray the area ────────────────────────────────
    tankLevelL -= required;
    ++spraySessionsDone;

    std::cout << "\n" << name << ": Spraying " << areaSqM
              << " m² with " << chemicalName
              << " (" << modeToString(mode) << ")\n"
              << "  Used     : " << required   << " L\n"
              << "  Remaining: " << tankLevelL << " L\n";

    return true;
}

void SprayerBot::statusReport() const {
    Robot::statusReport();
    std::cout << "  Mode         : " << modeToString(mode) << "\n"
              << "  Chemical     : " << chemicalName        << "\n"
              << "  Tank         : " << tankLevelL
                                     << " / " << tankCapacityL << " L\n"
              << "  Spray Rate   : " << sprayRateL_per_m2   << " L/m²\n"
              << "  Sessions Done: " << spraySessionsDone    << "\n";
}

// ══════════════════════════════════════════════════════════════
//  HARVESTING BOT
// ══════════════════════════════════════════════════════════════
std::string HarvestingBot::statusToString(Plot::Status status) {
    switch (status) {
        case Plot::Status::SEED:  return "Seed";
        case Plot::Status::PLANT: return "Plant";
        case Plot::Status::DEAD:  return "Dead";
    }
    return "Unknown";
}

HarvestingBot::HarvestingBot(const std::string& id)
    : Robot(id, "HarvestingBot-" + id),
      totalHarvestedKg(0.0),
      totalDeadKg(0.0),
      totalPlantKg(0.0),
      harvests(0) {}

bool HarvestingBot::evaluateAndHarvest(const CropData   farm[3][3],
                                       int              r,
                                       int              c,
                                       Plot::Status status) {
    // ── Step 1: Get CropData from farm array ──────────────────
    CropData    cropData = farm[r][c];
    std::string cropName = cropData.getName();

    // ── Step 2: Generate random yield between 80-100% of 1kg ──
    std::random_device             rd;
    std::mt19937                   gen(rd());
    std::uniform_real_distribution dist(0.80, 1.00);

    double maxYieldKg    = 1.0;
    double percentage    = dist(gen);
    double expectedYield = maxYieldKg * percentage;

    std::cout << name << ": Scanning plot ["
              << r << "][" << c << "]\n"
              << "  Crop          : " << cropName                  << "\n"
              << "  Plot Status   : " << statusToString(status)    << "\n"
              << "  Time to Grow  : " << cropData.getTimeToGrow()       << " days\n"
              << "  Water/day     : " << cropData.getWaterReq() << " mL\n"
              << "  Max Yield     : " << maxYieldKg                << " kg\n"
              << "  Yield %       : " << percentage * 100          << "%\n"
              << "  Expected Yield: " << expectedYield             << " kg\n";

    // ── Step 3: Calculate yield based on status ───────────────
    switch (status) {
        case Plot::Status::SEED:
            std::cout << "  Seed detected – too early. Skipping.\n";
            return false;

        case Plot::Status::PLANT:
            std::cout << "  Plant ready – harvesting "
                      << expectedYield << " kg of " << cropName << "...\n";
            totalPlantKg     += expectedYield;
            totalHarvestedKg += expectedYield;
            log.push_back({cropName, status, expectedYield});
            ++harvests;
            std::cout << "  Yield           : " << expectedYield   << " kg\n"
                      << "  Plant harvested : " << totalPlantKg     << " kg\n"
                      << "  Total harvested : " << totalHarvestedKg << " kg\n";
            return true;

        case Plot::Status::DEAD: {
            double deadYield = expectedYield * 0.5;
            std::cout << "  Dead crop – collecting "
                      << deadYield << " kg of " << cropName << "...\n";
            totalDeadKg      += deadYield;
            totalHarvestedKg += deadYield;
            log.push_back({cropName, status, deadYield});
            ++harvests;
            std::cout << "  Yield           : " << deadYield        << " kg\n"
                      << "  Dead collected  : " << totalDeadKg      << " kg\n"
                      << "  Total harvested : " << totalHarvestedKg << " kg\n";
            return true;
        }
    }
    return false;
}

/*
sss
*/

void HarvestingBot::statusReport() const {
    Robot::statusReport();
    std::cout << "  Harvests Done  : " << harvests         << "\n"
              << "  Total Harvested: " << totalHarvestedKg << " kg\n"
              << "    Plant        : " << totalPlantKg     << " kg\n"
              << "    Dead         : " << totalDeadKg      << " kg\n";

    if (!log.empty()) {
        std::cout << "  Harvest Log:\n";

        std::cout << "    [Plant Harvests]\n";
        bool anyPlant = false;
        for (const auto& r : log) {
            if (r.status == Plot::Status::PLANT) {
                std::cout << "      " << r.cropName
                          << " | "   << r.yieldKg << " kg\n";
                anyPlant = true;
            }
        }
        if (!anyPlant) std::cout << "      (none)\n";

        std::cout << "    [Dead Harvests]\n";
        bool anyDead = false;
        for (const auto& r : log) {
            if (r.status == Plot::Status::DEAD) {
                std::cout << "      " << r.cropName
                          << " | "   << r.yieldKg << " kg\n";
                anyDead = true;
            }
        }
        if (!anyDead) std::cout << "      (none)\n";
    }
}