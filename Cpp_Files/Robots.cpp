#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>

#include "Header_Files/Robots.h"

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