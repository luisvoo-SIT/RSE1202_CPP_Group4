#include "CropsV2.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <istream>

using namespace std;


Crop::Crop(string n, int minH, int maxH, int minT, int maxT,
           int minUV, int maxUV, int water, int timeToGrow) {
    name = n;
    minHumidity = minH;
    maxHumidity = maxH;
    minTemperature = minT;
    maxTemperature = maxT;
    minUVIntensity = minUV;
    maxUVIntensity = maxUV;
    waterRequirement = water;
    this->timeToGrow = timeToGrow;
}

vector<Crop> Crop::loadCrops(const string &filename) {
    vector<Crop> crops;
    string line; // 
    size_t location; // for parsing CSV
    stringstream ss(line);
    string token;
    vector<string> fields;

    //cout<<"Type your filename"<<endl;
    //cin>>filename;
    cout << "Loading crops from file: " << filename << endl;
    ifstream file(filename);
    getline(file, line);
    cout << "Header: " << line << endl; // Print the header for verification

 while (getline(file, line)) {
    if (line.empty()) continue;

    stringstream ss(line);
    string token;
    vector<string> fields;
    while (getline(ss, token, ',')) {
        fields.push_back(token);
    }

    if (fields.size() < 9) continue;

    string localName;
    int minH, maxH, minT, maxT, minUV, maxUV, water, timeToGrow;

    localName  = fields[0];                                                 // convert numeric fields using stoi to prevent type errors
    minH       = stoi(fields[1]);
    maxH       = stoi(fields[2]);
    minT       = stoi(fields[3]);
    maxT       = stoi(fields[4]);
    minUV      = stoi(fields[5]);
    maxUV      = stoi(fields[6]);
    water      = stoi(fields[7]);
    timeToGrow = stoi(fields[8]);

    crops.push_back(Crop(localName, minH, maxH, minT, maxT, minUV, maxUV, water, timeToGrow));
    cout << "All crops loaded" << endl; 

}
return crops;
}

    //I need to add a loop to read each line of the file and create Crop objects accordingly, and then store them in a vector for later use
    //but vector can only store one type of data, so I need to create a struct or class to hold the crop data,
    //and then create a vector of that struct or class to store all the crops loaded from the file


void Crop::displaycropsinfo() {
    cout << "Name: " << name << "\n"
         << "  Humidity range: " << minHumidity << " - " << maxHumidity << "\n"
         << "  Temperature range: " << minTemperature << " - " << maxTemperature << "\n"
         << "  UV intensity range: " << minUVIntensity << " - " << maxUVIntensity << "\n"
         << "  Water requirement: " << waterRequirement << "\n"
         << "  Time to grow: " << timeToGrow << " units\n";
         <<"-----------------------------\n";
}    

string Crop::getName() {
    return name;
}
string Crop::getTimetoGrow() {
    return timeToGrow;
}
string Crop::getwaterRequirements() {
    return waterRequirement;
}


    // Implementation for loading crops from file


// Test function to verify user input loading works
void testUserInput() {
    string filename;

    cout << "=== Crops User Input Test ===" << endl;
    cin >> filename;
    cout << "Test completed successfully!\n";

}

int main() {    
    vector<Crop> crops = Crop::loadCrops("Crop_Info.csv");
    cout << "Total crops loaded: " << crops.size() << endl;

    for (size_t i = 0; i < crops.size(); ++i) {
        cout << "\n--- Crop " << i+1 << " ---\n";
        crops[i].name;
    }


    return 0;
}