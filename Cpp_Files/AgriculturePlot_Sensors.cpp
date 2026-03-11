#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Stores the requirements for each crop from crops.csv
struct CropData {
    string name;
    int minHum, maxHum;
    int minTemp, maxTemp;
    int minUV, maxUV;
    double waterReq;
    int timeToGrow;
};

// Represents one 3x3 Sector
struct Plot {
    string cropName = "Empty";
    char symbol = ' ';
    float currentTemp = 20.0;
    float currentHum = 60.0;
};

vector<CropData> loadCrops() {
    vector<CropData> crops;
    ifstream file("crops.csv");
    string line;

    // Skip the header row
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        CropData c;
        string temp;

        getline(ss, c.name, ',');
        getline(ss, temp, ','); c.minHum = stoi(temp);
        getline(ss, temp, ','); c.maxHum = stoi(temp);
        getline(ss, temp, ','); c.minTemp = stoi(temp);
        getline(ss, temp, ','); c.maxTemp = stoi(temp);
        getline(ss, temp, ','); c.minUV = stoi(temp);
        getline(ss, temp, ','); c.maxUV = stoi(temp);
        getline(ss, temp, ','); c.waterReq = stod(temp);
        getline(ss, temp, ','); c.timeToGrow = stoi(temp);

        crops.push_back(c);
    }
    return crops;
}

void displayFarm(const vector<vector<Plot>>& farm) {
    cout << "\n--- VERTICAL FARM 3x3 SECTOR GRID ---" << endl;
    
    for (int i = 0; i < 3; i++) { // Farm Row
        for (int spaceRow = 0; spaceRow < 3; spaceRow++) { // Internal Row
            for (int j = 0; j < 3; j++) { // Farm Column
                
                // Draw the 3 spaces for this specific plot
                for (int spaceCol = 0; spaceCol < 3; spaceCol++) {
                    cout << "[" << farm[i][j].symbol << "]";
                }
                
                // Vertical divider between plots
                if (j < 2) cout << " | ";
            }
            cout << endl;
        }
        // Horizontal divider between plots
        if (i < 2) cout << "-----------------------+-----------------------+-----------------------" << endl;
    }
}

void manageFarm() {
    vector<CropData> availableCrops = loadCrops();
    // Create 3x3 grid of Plots
    vector<vector<Plot>> farm(3, vector<Plot>(3));

    int choice = 0;
    while (choice != 3) {
        cout << "\n1. View Farm Layout\n2. Plant Crop\n3. Return to C&C\nChoice: ";
        cin >> choice;

        if (choice == 1) {
            displayFarm(farm);
        } 
        else if (choice == 2) {
            int r, c, cropIdx;
            cout << "Select Sector Row (0-2) and Col (0-2): ";
            cin >> r >> c;

            cout << "Available Crops:\n";
            for (int i = 0; i < availableCrops.size(); i++) {
                cout << i << ". " << availableCrops[i].name << endl;
            }
            cout << "Select Crop Index: ";
            cin >> cropIdx;

            farm[r][c].cropName = availableCrops[cropIdx].name;
            farm[r][c].symbol = availableCrops[cropIdx].name[0]; // Use first letter
            
            cout << "Planted " << farm[r][c].cropName << " in Sector [" << r << "][" << c << "]" << endl;
        }
    }
}

int main() {
    manageFarm();
    return 0;
}