#include "Header_Files/CropsV2.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <istream>

using namespace std;


CropData::CropData(string n, int minH, int maxH, int minT, int maxT,
           int minUV, int maxUV, double water, int time) {
    name      = n;
    minHum    = minH;
    maxHum    = maxH;
    minTemp   = minT;
    maxTemp   = maxT;
    minUV     = minUV;
    maxUV     = maxUV;
    waterReq  = water;
    timeToGrow = time;
}

vector<CropData> CropData::loadCrops() {
    vector<CropData> crops;
    ifstream file("Crop_Info.csv");
    string line;

    // Skip the header row
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string temp;
        string name;
        int minH, maxH, minT, maxT, minUV, maxUV, time;
        double water;

        getline(ss, name,  ',');
        getline(ss, temp,  ','); minH  = stoi(temp);
        getline(ss, temp,  ','); maxH  = stoi(temp);
        getline(ss, temp,  ','); minT  = stoi(temp);
        getline(ss, temp,  ','); maxT  = stoi(temp);
        getline(ss, temp,  ','); minUV = stoi(temp);
        getline(ss, temp,  ','); maxUV = stoi(temp);
        getline(ss, temp,  ','); water = stod(temp);
        getline(ss, temp,  ','); time  = stoi(temp);

        crops.push_back(CropData(name, minH, maxH, minT, maxT,
                                  minUV, maxUV, water, time));

        //cout << "Loaded crop: " << name << "\n";
    }
    return crops;
}

    //I need to add a loop to read each line of the file and create Crop objects accordingly, and then store them in a vector for later use
    //but vector can only store one type of data, so I need to create a struct or class to hold the crop data,
    //and then create a vector of that struct or class to store all the crops loaded from the file

/*
void CropData::displaycropsinfo() {
    cout << "Name: " << name << "\n"
         << "  Humidity range: " << minHumidity << " - " << maxHumidity << "\n"
         << "  Temperature range: " << minTemperature << " - " << maxTemperature << "\n"
         << "  UV intensity range: " << minUVIntensity << " - " << maxUVIntensity << "\n"
         << "  Water requirement: " << waterRequirement << "\n"
         << "  Time to grow: " << timeToGrow << " units\n"
         << "-------------------------------";
}    
*/
string CropData::getName() const { return name; }
int CropData::getMinHum() const { return minHum; }
int CropData::getMaxHum() const { return maxHum; }
int CropData::getMinTemp() const { return minTemp; }
int CropData::getMaxTemp() const { return maxTemp; }
int CropData::getMinUV() const { return minUV; }
int CropData::getMaxUV() const { return maxUV; }
double CropData::getWaterReq() const { return waterReq; }
int CropData::getTimeToGrow() const { return timeToGrow; }

    // Implementation for loading crops from file

/*
// Test function to verify user input loading works
void testUserInput() {
    string filename;

    cout << "=== Crops User Input Test ===" << endl;
    cin >> filename;
    cout << "Test completed successfully!\n";

}
*/

/*
int main(){
    vector<CropData> availableCrops = CropData::loadCrops();
    cout<<CropData::getName();
}
*/
