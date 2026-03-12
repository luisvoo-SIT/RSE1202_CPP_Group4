#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>

#include "Header_Files/Robots.h"
#include "Header_Files/seedingBot.h"
#include "CropsV2.h"

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
    
    cout << "  Crop         : " << assignedCrop.getName()             << "\n"
         << "  Time to Grow : " << assignedCrop.getTimetoGrow()       << " days\n"
         << "  Humidity     : " << assignedCrop.getMinHumidity()
                                << " - " << assignedCrop.getMaxHumidity()    << " %\n"
         << "  Temperature  : " << assignedCrop.getMinTemperature()
                                << " - " << assignedCrop.getMaxTemperature() << " C\n"
         << "  UV Intensity : " << assignedCrop.getMinUVIntensity()
                                << " - " << assignedCrop.getMaxUVIntensity() << "\n"
         << "  Water/day    : " << assignedCrop.getwaterRequirements() << " mL\n"
         << "  Seeds Planted: " << seedsPlanted                       << "\n";
}