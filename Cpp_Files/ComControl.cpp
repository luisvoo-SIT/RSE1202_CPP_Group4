#include "CommControl.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "Header_Files/CropsV2.h"

using namespace std;

// ... (Constructor remains the same)

void CommControl::displayMainMenu() {
    int choice = 0;
    while (choice != 5) { // Adjusted exit number
        cout << "\n========== VERTICAL FARMING C&C ==========" << endl;
        cout << "1. Robot Fleet Management (Status & Tasks)" << endl; // Combined
        cout << "2. View Vegetation Plots (Layout)" << endl;
        cout << "3. Change Simulation Time" << endl;
        cout << "4. View History Logs" << endl;
        cout << "5. Exit Simulation" << endl;
        cout << "Selection: ";
        cin >> choice;

        switch (choice) {
            case 1: manageRobots(); break; // New combined function
            case 2: displayPlotLayout(); break;
            case 3: displayTimeControlMenu(); break; 
            case 4: displayHistory(); break;
            case 5: cout << "Shutting down C&C..." << endl; break;
            default: cout << "Invalid choice." << endl;
        }
    }
}

// New function to handle the combined Robot logic
void CommControl::manageRobots() {
    int robotChoice;
    cout << "\n--- ROBOT FLEET MANAGEMENT ---" << endl;
    displayRobotStatus(); // First, show the status of all robots
    
    cout << "\nWould you like to assign a task?" << endl;
    cout << "1. Yes, Assign Task" << endl;
    cout << "2. No, Return to Main Menu" << endl;
    cout << "3. Emergency Manual Override" << endl; // Good place for the override!
    cout << "Selection: ";
    cin >> robotChoice;

    if (robotChoice == 1) {
        assignTask();
    } else if (robotChoice == 3) {
        performOverride();
    }
}

// --- 1. Vegetation Plots & Sensors ---
void CommControl::displayPlotLayout() {
    cout << "\n========== VEGETATION PLOT LAYOUT ==========" << endl;
    /*cout << left << setw(10) << "SECTOR" << setw(15) << "CROP" << setw(10) << "HUMIDITY" << "STATUS" << endl;
    cout << "--------------------------------------------" << endl;
    
    // Example static data (In your project, this comes from the Agriculture Plot class)
    cout << setw(10) << "S-01" << setw(15) << "Coriander" << setw(10) << "65%" << "HEALTHY" << endl;
    cout << setw(10) << "S-02" << setw(15) << "Coriander" << setw(10) << "42%" << "NEEDS WATER" << endl;
    cout << setw(10) << "S-03" << setw(15) << "Empty" << setw(10) << "N/A" << "READY" << endl;*/
    
    addLog("Inspected Sector Layout and Sensors", false);
}

// --- 2. Actuators Display ---
void CommControl::displayActuatorStatus() {
    cout << "\n========== ACTUATOR CONTROL STATUS ==========" << endl;
    cout << left << setw(15) << "ACTUATOR" << setw(10) << "STATE" << "POWER DRAW" << endl;
    cout << "--------------------------------------------" << endl;
    
    // These would represent the hardware components like lights and pumps
    cout << setw(15) << "UV Light A1" << setw(10) << "ON" << "150W" << endl;
    cout << setw(15) << "Water Pump B" << setw(10) << "OFF" << "0W" << endl;
    cout << setw(15) << "Ventilation" << setw(10) << "ON" << "45W" << endl;
    
    cout << "\n========== RESOURCE USAGE DATA ==========" << endl;
    // This displays the "Results" which can be affected by your Time Change feature
    double totalWater = 150.5 * simulationSpeed; // Example scaling
    double totalPower = 1200.0 * simulationSpeed;

    cout << "Simulation Speed: " << simulationSpeed << "x" << endl;
    cout << "--------------------------------------------" << endl;
    cout << "Total Water Consumed:  " << totalWater << " Liters" << endl;
    cout << "Total Power Consumed:  " << totalPower << " Watts" << endl;
    cout << "Estimated Yield:       " << "45.0 kg (Coriander)" << endl;
    
    addLog("Generated Usage Data Report", false);
}

// --- 4. Main Menu Update ---
// Make sure to add these options to your main switch case
void CommControl::displayMainMenu() {
    int choice = 0;
    while (choice != 5) {
        cout << "\n--- MAIN CONTROL PANEL ---" << endl;
        cout << "1. Robot Fleet Management" << endl;
        cout << "2. Vegetation Plots & Sensors" << endl;
        cout << "3. Actuator Status" << endl;
        cout << "4. Resource Usage Data" << endl;
        cout << "5. Exit" << endl;
        cout << "Selection: ";
        cin >> choice;

        switch (choice) {
            case 1: manageRobots(); break;
            case 2: displayPlotLayout(); break;
            case 3: displayActuatorStatus(); break;
            case 4: displayUsageData(); break;
            case 5: cout << "Exiting..." << endl; break;
        }
    }
}

int main() {
    displayMainMenu();
    return 0;
}

// ... (Rest of your functions like displayPlotLayout and assignTask stay the same)