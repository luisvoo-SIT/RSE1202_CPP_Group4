#include <iostream>
using namespace std;

class Crop {
private:
    int growthDaysMin,growthDaysMax;

    
    // Growth conditions
    float minHumidity ,maxHumidity, minTemperature, maxTemperature, minUVIntensity, maxUVIntensity, waterRequirement;


public:
    void Crop(string cropName, int minDays, int maxDays){
        cropName = cropName;
        growthDaysMin = minDays;
        growthDaysMax = maxDays;
    }
    void displayInfo()    {
        cout << "Crop Name: " << cropName << endl;
        cout << "Growth Days: " << growthDaysMin << " - " << growthDaysMax << endl;
        cout << "Humidity Range: " << minHumidity << "% - " << maxHumidity << "%" << endl;
        cout << "Temperature Range: " << minTemperature << "°C - " << maxTemperature << "°C" << endl;
        cout << "UV Intensity Range: " << minUVIntensity << " - " << maxUVIntensity << endl;
        cout << "Water Requirement: " << waterRequirement << " liters/day" << endl;
    }
};
