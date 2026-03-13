#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>


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


    string getName() const ;
    int getTimetoGrow() const ;
    int getwaterRequirements() const ;
    int getminHumidity() const ;
    int getmaxHumidity() const ;
    int getminTemperature() const;
    int getmaxTemperature() const ;
    int getminUVIntensity() const;
    int getmaxUVIntensity() const ;
};

