#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class Crop {
protected:
    string name;
    int minHumidity;
    int maxHumidity;
    int minTemperature;
    int maxTemperature;
    int minUVIntensity;
    int maxUVIntensity;
    int waterRequirement;
    int timeToGrow;         

public:
    // Constructor
    Crop();

    vector<Crop> loadCrops(const string &filename);

    virtual void assignLoadedCrops(const vector<Crop> &loadedCrops);

    void displaycropsinfo();
};

