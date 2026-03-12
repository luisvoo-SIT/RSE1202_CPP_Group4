#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>

#include "Header_Files/Robots.h"
#include "Header_Files/seedingBot.h"
#include "Header_Files/CropsV2.h"

using namespace std;

Robot::Robot(const string& id, const string& name)
    : id(id), name(name), batteryLevel(100.0), isOperational(true) {}

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
    plantSeeds(100);
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

int main() 
{
    // ── Step 1: Load crops from CSV file ─────────────────────
    vector<Crop> crops = Crop::loadCrops("Crop_Info.csv");

    if (crops.empty()) {
        cout << "No crops loaded. Check your CSV file.\n";
        return 1;
    }

    // ── Step 2: Display all available crops ──────────────────
    cout << "=== Available Crops ===\n";
    for (size_t i = 0; i < crops.size(); ++i) {
        cout << i + 1 << ". ";
        crops[i].displaycropsinfo();
    }

    // ── Step 3: Let user pick a crop ─────────────────────────
    int choice;
    cout << "\nSelect a crop number to assign to the seeding bot: ";
    cin  >> choice;

    if (choice < 1 || choice > (int)crops.size()) {
        cout << "Invalid choice.\n";
        return 1;
    }

    // ── Step 4: Create SeedingBot with selected crop ──────────
    Crop selectedCrop = crops[choice - 1];
    SeedingBot seeder("S01", selectedCrop);

    // ── Step 5: Show robot status before task ─────────────────
    cout << "\n=== Seeding Bot Status Before Task ===\n";
    seeder.statusReport();

    // ── Step 6: Run the seeding task ──────────────────────────
    cout << "\n=== Running Seeding Task ===\n";
    seeder.performTask();

    // ── Step 7: Show robot status after task ──────────────────
    cout << "\n=== Seeding Bot Status After Task ===\n";
    seeder.statusReport();

    // ── Step 8: Plant a custom number of seeds ────────────────
    int seedCount;
    cout << "\nHow many additional seeds to plant? ";
    cin  >> seedCount;
    seeder.plantSeeds(seedCount);

    // ── Step 9: Final status report ───────────────────────────
    cout << "\n=== Final Status ===\n";
    seeder.statusReport();

    return 0;
}