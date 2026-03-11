#ifndef COMMCONTROL_H
#define COMMCONTROL_H

#include <vector>
#include <string>

class CommControl {
public:
    // Constructor
    CommControl();

    // UI Display Functions (The "User View")
    void displayPlotLayout();       // Shows the grid of sectors
    void displayRobotStatus();      // Lists all robots and what they are doing
    void displayActuatorStatus();   // Shows if lights/pumps are ON or OFF
    void displayUsageData();        // Displays electricity/water consumption
    
    // Control Menus
    void displayTimeControlMenu();  // Menu to change simulation speed
    void displayMainMenu();         // The starting point for the user
    
    // Logic Functions
    void updateTime(int multiplier);
    void processUserInput();        // The loop that waits for user keys
};

#endif