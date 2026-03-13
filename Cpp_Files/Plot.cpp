#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
//#include "Robots.h"
//#include "TimeControl.h"
#include "Header_Files/CropsV2.h"

using namespace std;

//global variables:
int farmchoice = 0;

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

/*vector<CropData> loadCrops() {
    vector<CropData> crops;
    ifstream file("Crop_Info.csv");
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
*/
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
    vector<Crop> availableCrops = Crop::loadCrops("Crop_Info.csv");
    // Create 3x3 grid of Plots
    vector<vector<Plot>> farm(3, vector<Plot>(3));

    int choice = 0;
    int a, b = 0; //for error handling, not working

    while (choice != 8) {
        displayFarm(farm);
        //cout << "\n1. View Plot Layout\n2. Plant Crop\n3. Water Crop\n4. Harvest Crop\n5. Time Skip\n6. Return to Main Menu\n7. View Plot Layout\nChoice: ";
        cout << "\n1. View Plot\n2. Return to Main Menu\n   Choice: ";
        cin >> choice;

        /*if (choice == 1) {
            int r, c;
            cout << "Enter Plot Row (1-3): ";
            cin >> r;
            cout << "Enter Plot Column (1-3): ";
            cin >> c;

            // Validate input
            if (r < 1 || r > 3 || c < 1 || c > 3) {
                cout << "Invalid plot coordinates. Please enter values between 1 and 3." << endl;
                continue;
            }

            // Adjust for 0-based indexing
            r--; c--;

            cout << "\n--- PLOT DETAILS ---" << endl;
            cout << "Crop: " << farm[r][c].cropName << endl;
            cout << "Temperature: " << farm[r][c].currentTemp << "°C" << endl;
            cout << "Humidity: " << farm[r][c].currentHum << "%" << endl;
        } 

        else if (choice == 2) {
            int r, c, cropIdx, plotId;

            // Use a while loop to force valid input
            cout << "Select Plot ID (1-9): ";
            cin >> plotId;

            while (plotId < 1 || plotId > 9) {
                // Clear the error flag and ignore bad input in case they typed a letter
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                
                cout << "Invalid plot ID. "<< endl << "Please enter a number between 1 and 9: ";
                cin >> plotId;
            }

            // Convert plot ID to row and column indices
            r = (plotId - 1) / 3;
            c = (plotId - 1) % 3;

            cout << "Available Crops:\n";
            for (int i = 0; i < availableCrops.size(); i++) {
                cout << i + 1 << ". " << availableCrops[i].name << endl;
            }
            cout << "Select Crop Index: ";
            cin >> cropIdx;

            farm[r][c].cropName = availableCrops[cropIdx - 1].name;
            farm[r][c].symbol = availableCrops[cropIdx - 1].name[0]; // Use first letter

            cout << "Planted " << farm[r][c].cropName << " in Sector [" << r << "][" << c << "]" << endl;

            
        }

        else if (choice == 3) {
            //Water Crop
            cout << "Watering Crops..." << endl;
            cout << "Enter Robot Function..." << endl;

        }

        else if (choice == 4) {
            //Harvest Crop
            cout << "Harvesting Crops..." << endl;
            cout << "Enter Robot Function..." << endl;
        }

        else if (choice == 5) {
            //Time Skip
            cout << "Skipping time..." << endl;
            cout << "Enter Time Skip Function..." << endl;
        }*/

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
                    a++;
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
                    
                    while (true) {
                        cout << "Please select an option from the following: " << endl;
                        cout << "1. Plant new crop" << endl;
                        cout << "2. Harvest crop" << endl;
                        cout << "3. Apply Pesticide" << endl;
                        cout << "4. View Other Plots" << endl;
                        cout << "5. Skip the Day" << endl;
                        cout << "6. Return to Menu" << endl << endl;
                        cout << "Select Your Option: ";
                        cin >> farmchoice;

                        if (farmchoice < 1 || farmchoice > 9) {
                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(1000, '\n');
                            }
                            cout << "Invalid option. Try again." << endl;
                        }
                    
                        else {
                                switch (farmchoice)
                                {
                                    case 1: //call planting robot
                                        cout << "Planting new crop" << endl;
                                        //plantrobot();
                                        break;
                                    case 2: //call harvesting robot 
                                        cout << "harvest da crop" << endl;
                                        //harvestbot();
                                        break;
                                    case 3: //call pesticide robot
                                        cout << "deleting pests" << endl;
                                        //pestbot();
                                        break;
                                    case 4: //viewing other plots
                                        cout << "viewing plots" << endl;    
                                        manageFarm();
                                        break;
                                    case 5: //time skip (1 day increments)
                                        cout << "zzzzz" << endl;
                                        //time++;
                                        break;
                                    case 6: //back to main menu
                                        cout << "menu" << endl;
                                        //mainmenu.cpp
                                        break;
                                    default:
                                        break;
                                }
                            }
                        break;
                    } 

                }
            }
        }
        
        else if (choice == 2) {
            //Return to Main Menu
            cout << "Returning to main menu..." << endl;
        }
    }
}
    
/*
int main() {
    //manageFarm();
    vector<Crop> crops = Crop::loadCrops("Crop_Info.csv");
    cout << "Total crops loaded: " << crops.size() << endl;
    for (size_t i = 0; i < crops.size(); ++i) 
    {
        cout << "\n--- Crop " << i+1 << " ---\n";
        cout << crops[i].getName() << endl;
    }
    return 0;
}
*/