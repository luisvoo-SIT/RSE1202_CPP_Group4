#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
//#include "Robots.h"
//#include "TimeControl.h"
 

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
    ifstream file("Crop_Info.csv");
    string line;

    // Skip the header row
    getline(file, line);
 //test
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

    while (choice != 8) {
        displayFarm(farm);
        //cout << "\n1. View Plot Layout\n2. Plant Crop\n3. Water Crop\n4. Harvest Crop\n5. Time Skip\n6. Return to Main Menu\n7. View Plot Layout\nChoice: ";
        cout << "\n1. View Plot\n2. Return to Main Menu\nnChoice: ";
        cin >> choice;


        if (choice == 1) {
            int plotId;

            while (true) {
                cout << "\nEnter Plot ID to view (1-9) or 0 to return: ";
                cin >> plotId;

                // Escape condition
                if (plotId == 0) {
                    cout << "Returning to menu..." << endl;
                    break; 
                }

                // Validation
                if (plotId < 1 || plotId > 9) {
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                    }
                    cout << "Invalid Plot ID. Try again." << endl;
                } else {
                    // Convert valid Plot ID to indices
                    int r = (plotId - 1) / 3;
                    int c = (plotId - 1) % 3;

                    cout << "\n===============================" << endl;
                    cout << "      VIEWING PLOT ID: " << plotId << endl;
                    cout << "===============================" << endl;

                    // Display the 3x3 visual for JUST this plot
                    for (int i = 0; i < 3; i++) {
                        cout << "       "; // Indent for looks
                        for (int j = 0; j < 3; j++) {
                            cout << "[" << farm[r][c].symbol << "]";
                        }
                        cout << endl;
                    }

                    // Display the metadata
                    cout << "-------------------------------" << endl;
                    cout << "Crop Name:   " << farm[r][c].cropName << endl;
                    cout << "Temperature: " << farm[r][c].currentTemp << "°C" << endl;
                    cout << "Humidity:    " << farm[r][c].currentHum << "%" << endl;
                    cout << "-------------------------------" << endl;

                    cout << "Press Enter to return to menu...";
                    cin.ignore(); // Clear the newline from previous input
                    cin.get(); // Wait for Enter key
                    
                    break; // Exit after showing details
                }
            }
        }
        
        else if (choice == 2) {
            //Return to Main Menu
            cout << "Returning to main menu..." << endl;
        }
    }

}
    

int main() {
    manageFarm();
    return 0;
}