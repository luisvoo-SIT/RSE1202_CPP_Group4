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
    Crop(string name, int minH, int maxH, int minT, int maxT,
     int minUV, int maxUV, int water, int timeToGrow);

    static vector<Crop> loadCrops(const string &filename);

    //virtual void assignLoadedCrops(const vector<Crop> &loadedCrops);

    void displaycropsinfo();


    string getName();
    int getTimetoGrow();
    int getwaterRequirements();
    int getminHumidity();
    int getmaxHumidity();
    int getminTemperature();
    int getmaxTemperature();
    int getminUVIntensity();
    int getmaxUVIntensity();
};

