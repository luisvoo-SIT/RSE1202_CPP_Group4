#include "WateringSystem.h"

void WateringSystem::adjustWateringLevel(int moistureLevel)
{
    // If soil is dry (moisture level < 50%), increase watering level
    if (moistureLevel < 50)
    {
        actuatorLevel = 100;
        cout << "\n>>>Soil is dry, increasing watering level to " << actuatorLevel << "%.\n" << endl;
    }

    else
    {
        actuatorLevel = 0;
        cout << "\n>>>Soil has sufficient moisture level, no watering is required.\n" << endl;
    }
}