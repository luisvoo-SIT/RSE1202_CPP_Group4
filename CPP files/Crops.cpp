#include "CropsV2.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

use namespace std;


Crop::Crop()
{
    name = "Placeholder Crop";
    minHumidity = 0;
    maxHumidity = 100;
    minTemperature = 0;
    maxTemperature = 100;
    minUVIntensity = 0;
    maxUVIntensity = 100;
    waterRequirement = 0;
    timeToGrow = 0;
}

void Crop::loadCrops(const string &filename) {
    vector<Crop> crop;
    string line; // 
    string filename;

    cout<<"Type your filename"<<endl;
    cin>>filename;
    cout << "Loading crops from file: " << filename << endl;
    ifstream file(filename);
    getline(file, line);
 

    
    }
    // Implementation for loading crops from file
}

// Test function to verify user input loading works
void testUserInput() {
    std::cout << "=== Crops User Input Test ===" << std::endl;
    std::vector<Crop> crops = UserInputLoad();
    std::cout << "Test completed successfully!\n";
}