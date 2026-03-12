#include "WateringSystem.h"

int main()
{
    // Clear console screen
    system("cls"); 

    // Create object of watering system class
    WateringSystem ws;

    // Display inital watering system level
    ws.displayActuatorLevel();

    // Simulating soil moisture level via manual user input
    int moistureLevel;
    cout << "\n>>>Enter soil moisture level (0-100%): ";
    cin >> moistureLevel;

    // Display current soil moisture level
    cout << "\n>>>Current soil moisture level is: " << moistureLevel << "%" << endl;

    // Watering system adjust watering level based on soil moisture level (simulated via user input)
    ws.adjustWateringLevel(moistureLevel);

    // Display updated watering system level
    ws.displayActuatorLevel();

    // Exit message
    cout << "\n>>> Goodbye for now :)\n" << endl;

    return 0;

}
