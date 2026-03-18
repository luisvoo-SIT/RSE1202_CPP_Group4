#pragma once
#include <string>
#include <vector>


using namespace std;

class CropData {
 

protected:
    string name;
    int minHum, maxHum;
    int minTemp, maxTemp;
    int minUV, maxUV;
    double waterReq;
    int timeToGrow;    

public:
    // Constructor
    CropData(string name, int minH, int maxH, int minT, int maxT,
     int minUV, int maxUV, double water, int timeToGrow);

    

    //virtual void assignLoadedCrops(const vector<Crop> &loadedCrops);
    static vector<CropData> loadCrops(); 
    void displaycropsinfo();

    string getName() const;
    int getMinHum() const;
    int getMaxHum() const;
    int getMinTemp() const;
    int getMaxTemp() const;
    int getMinUV() const;
    int getMaxUV() const;
    double getWaterReq() const;
    int getTimeToGrow() const;

    };
    
