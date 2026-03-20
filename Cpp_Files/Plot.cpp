#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>


//chee hui's bot functions
#include "Header_Files/Robots.h" 
#include "Header_Files/seedingBot.h"
#include "Header_Files/SprayerBot.h"
#include "Header_Files/HarvestBot.h"
#include "Header_Files/FileWriter.h"

//global time function
#include "Header_Files/time.h"

//actuator functions
#include "Header_Files/Actuators.h"
#include "Header_Files/Controls.h"

//crop data functions
#include "Header_Files/CropsV2.h" //luis' crop data

//plot functions
#include "Header_Files/plotv2.h"

using namespace std;

//global variables:
int farmchoice = 0;
int GlobalTime = 0; //how long farm has been running for
int warning = 0; //warning for crop health, if warning reaches 2, crop dies

//things to initialize:
WaterSystemControl wsc;
Plot::Status cropstatus (int i, int r, int c);
FileWriter fw; //file writer initialization

//bot initializations
string seedbotname = "S01"; //seeding bot initialization
HarvestingBot harvester ("H01"); //harvest bot initialization
SprayerBot sprayer("SP01", 100.0, 0.5); //sprayer bot initialization

//plot time initialization
TimeControl advancePlotTime; //time control initialization

//global vector initialization:
vector<CropData> availableCrops = CropData::loadCrops();
vector<vector<Plot>> farm(3, vector<Plot>(3));
SeedingBot seeder (seedbotname, availableCrops[0]);


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

//prep for manageFarm
CropData* getCropDataByName(const string& cropName) {
    for (auto& crop : availableCrops) {
        if (crop.getName() == cropName) {
            return &crop;
        }
    }
    return nullptr;
}
// warning counter to track per plot and not globally
static int plotWarnings[3][3] = {0};

void manageFarm() {
    int plotId;

    while (true) {
        cout << "\nEnter Plot ID to view (1-9), or 0 to exit the program: ";
        if (!(cin >> plotId)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number between 1 and 9 (or 0 to return)." << endl;
            continue;
        }
        if (plotId == 0) { //exit program
                cout << "\nExiting SAGE Simulator...\n";
                std::exit(0); // Exit the program with success status
                break;
                }
        if (plotId < 1 || plotId > 9) {
            cout << "Invalid Plot ID. Please enter a number between 1 and 9 (or 0 to return)." << endl;
            continue;
        }

        else {
            // Convert valid Plot ID to indices
            int r = (plotId - 1) / 3;
            int c = (plotId - 1) % 3;

            cout << "\n===============================" << endl;
            cout << "      VIEWING PLOT ID: " << plotId << endl;
            cout << "===============================" << endl;

            // Display the 3x3 visual for JUST this plot
            for (int i = 0; i < 3; i++) {
                cout << "       ";
                for (int j = 0; j < 3; j++) {
                    cout << "[" << farm[r][c].symbol << "]";
                }
                cout << endl;
            }

            // Display Plot Data
            cout << "-------------------------------" << endl;

            cout << "Crop Name:   " << farm[r][c].cropName << endl;
            cout << "Crop Status: " << farm[r][c].StatusNames[farm[r][c].cropstatus] << endl;
            cout << "Temperature: " << farm[r][c].currentTemp << "°C" << endl;
            cout << "Humidity:    " << farm[r][c].currentHum << "%" << endl;
            if (farm[r][c].currentWater < 0) farm[r][c].currentWater = 0;
            cout << "Water Level: " << farm[r][c].currentWater << endl;
            cout << "Time Planted: " << farm[r][c].PlotTime << " days" << endl;
            cout << "Global Time: " << GlobalTime << " days" << endl;
            cout << "Fertilizer Applied: " << (farm[r][c].fertilizersprayed ? "Yes" : "No") << endl;
            cout << "Pesticide Applied: " << (farm[r][c].pestsprayed ? "Yes" : "No") << endl;
            cout << "Herbicide Applied: " << (farm[r][c].herbsprayed ? "Yes" : "No") << endl;
            cout << "-------------------------------" << endl;

            cout << "Press Enter to return to menu...";
            cin.ignore();
            cin.get();

            while (true) {
                cout << "Please select an option from the following: " << endl;
                cout << "1. Plant new crop" << endl;
                cout << "2. Harvest crop" << endl;
                cout << "3. Apply Pesticide" << endl;
                cout << "4. View Other Plots" << endl;
                cout << "5. Skip the Day" << endl;
                cout << "6. Water Plants" << endl;
                cout << "7. Generate Farm Logs" << endl << endl;
                cout << "Select Your Option: ";
                cin >> farmchoice;

                if (farmchoice < 1 || farmchoice > 7) {
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                    }
                    cout << "Invalid option. Try again." << endl;
                }

                else {
                    switch (farmchoice) {
                    case 1: //call planting robot
                        cout << "planting new crop" << endl;
                        if (farm[r][c].cropName == "Empty") {
                            CropData plant = seeder.plantSeeds(1, availableCrops);
                            farm[r][c].cropName = plant.getName();

                            farm[r][c].symbol = plant.getName()[0]; // to get the char of the crop

                            cout << "\n=== Selected Crop Data ===\n"
                                 << "  Crop         : " << plant.getName() << "\n"
                                 << "  Time to Grow : " << plant.getTimeToGrow() << " days\n"
                                 << "  Water/day    : " << plant.getWaterReq() << " mL\n"
                                 << "  Humidity     : " << plant.getMinHum()
                                 << " - " << plant.getMaxHum() << " %\n"
                                 << "  Temperature  : " << plant.getMinTemp()
                                 << " - " << plant.getMaxTemp() << " C\n"
                                 << "  UV Intensity : " << plant.getMinUV()
                                 << " - " << plant.getMaxUV() << "\n";

                            farm[r][c].cropstatus = Plot::Status::SEED;
                            farm[r][c].PlotTime = 0;
                            plotWarnings[r][c] = 0;
                        }
                        else {
                            cout << "Plot already has a crop." << endl;
                        }
                        break;

                    case 2: //call harvesting robot
                        if (farm[r][c].cropName != "Empty") {
                            cout << "Crop found. Attempting harvest..." << endl;
                            Plot::Status status = static_cast<Plot::Status>(farm[r][c].cropstatus);
                            harvester.evaluateAndHarvest(availableCrops[0], status);

                            if (farm[r][c].cropstatus == Plot::Status::SEED) break;

                            farm[r][c].cropstatus = Plot::Status::EMPTY;
                            farm[r][c].symbol =' ';
                            farm[r][c].PlotTime = 0;
                            farm[r][c].currentWater = 0;
                            farm[r][c].currentTemp = 20.0;
                            farm[r][c].currentHum = 60.0;
                            farm[r][c].currentWater = 0;
                            farm[r][c].cropName = "Empty";
                            plotWarnings[r][c] = 0;

                            farm[r][c].fertilizersprayed = false;
                            farm[r][c].pestsprayed = false;
                            farm[r][c].herbsprayed = false;
                        }
                        else {
                            cout << "No crop to harvest." << endl;
                        }
                        break;

                    case 3: //call spraying robot
                        if (farm[r][c].cropName != "Empty") {
                            cout << "Crop found. Attempting spray..." << endl;
                            string chemical = sprayer.sprayArea(10.0);
                            sprayer.statusReport();

                            if (chemical == "PesticideX") {
                                farm[r][c].pestsprayed = true;
                                chemical.clear();
                            }
                            else if (chemical == "HerbicideY") {
                                farm[r][c].herbsprayed = true;
                                chemical.clear();
                            }
                            else if (chemical == "NitrogenFert") {
                                farm[r][c].fertilizersprayed = true;
                                chemical.clear();
                            }
                            else {
                                cout << "No Chemical Sprayed" << endl;
                            }
                            break;
                        }
                        else {
                            cout << "No crop to apply pesticide." << endl;
                        }
                        break;

                    case 4: //viewing other plots
                        cout << "viewing other plots..." << endl;
                        break;

                    case 5: { //time skip for ALL plots
                        unsigned int skip;
                        cout << "How many days to skip? Please enter a number between 0 and 365: " << endl;
                        cin >> skip;

                        while (cin.fail() || skip > 365 || (cin.peek() != '\n' && cin.peek() != EOF)) {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << "Invalid input. Please enter a number between 0 and 365: " << endl;
                            cin >> skip;
                        }

                        for (unsigned int day = 0; day < skip; day++) {
                            GlobalTime++; // always advance global time once per skipped day

                            for (int i = 0; i < 3; i++) {
                                for (int j = 0; j < 3; j++) {
                                    // if no crop, do not increase PlotTime
                                    if (farm[i][j].cropName == "Empty") {
                                        farm[i][j].currentWater = 0;
                                        continue;
                                    }

                                    CropData* crop = getCropDataByName(farm[i][j].cropName);
                                    if (crop == nullptr) {
                                        cout << "Crop data not found for plot " << (i * 3 + j + 1) << "." << endl;
                                        continue;
                                    }

                                    // planted crop: PlotTime increases
                                    farm[i][j].PlotTime++;

                                    // decrease water by crop requirement
                                    farm[i][j].currentWater -= crop->getWaterReq();
                                    if (farm[i][j].currentWater < 0) {
                                        farm[i][j].currentWater = 0;
                                    }

                                    // insufficient water check
                                    if (farm[i][j].currentWater > (crop->getWaterReq() + 5) ||
                                        farm[i][j].currentWater < (crop->getWaterReq() - 5) ||
                                        farm[i][j].currentWater == 0) {
                                        //set water level to 0 if it goes below 0, and increase warning count afterwards
                                        if (farm[i][j].currentWater < 0) {farm[i][j].currentWater = 0;}
                                        
                                        plotWarnings[i][j]++;

                                        cout << "Your crop is dying, at Plot: " << (i * 3 + j + 1)
                                             << ", plot day: " << farm[i][j].PlotTime << endl;
                                        cout << "Crop water requires: " << crop->getWaterReq()
                                             << " liters of water per day." << endl;
                                        cout << "Current water level: " << farm[i][j].currentWater
                                             << " liters." << endl << endl;
                                    }
                                    else {
                                        // water is okay again, reset warning streak
                                        plotWarnings[i][j] = 0;
                                    }

                                    // status update
                                    if (plotWarnings[i][j] >= 2) {
                                        farm[i][j].cropstatus = Plot::Status::DEAD;
                                        farm[r][c].symbol     = 'X';
                                    }
                                    else if (farm[i][j].PlotTime >= crop->getTimeToGrow()) {
                                        farm[i][j].cropstatus = Plot::Status::PLANT;
                                        farm[r][c].symbol     = farm[r][c].cropName[0];     // ← first letter, lowercase
                                    }
                                    else {
                                        farm[i][j].cropstatus = Plot::Status::SEED;
                                        farm[r][c].symbol     = farm[r][c].cropName[0];
                                        farm[r][c].symbol     = tolower(farm[r][c].symbol); // ← lowercase = still growing
                                    }
                                }
                            }
                        }

                        cout << "Global Time has been advanced by " << skip << " days." << endl;
                        cout << "Updated farm status after time skip:" << endl;
                        cout << "Global Time: " << GlobalTime << " days" << endl;

                        for (int i = 0; i < 3; i++) {
                            for (int j = 0; j < 3; j++) {
                                if (farm[i][j].currentWater < 0) {farm[i][j].currentWater = 0;}
                                cout << "Plot " << (i * 3 + j + 1)
                                     << " | Crop: " << farm[i][j].cropName
                                     << " | Plot Time: " << farm[i][j].PlotTime
                                     << " | Water: " << farm[i][j].currentWater
                                     << " | Status: " << farm[i][j].StatusNames[farm[i][j].cropstatus]
                                     << endl;
                            }
                        }
                        break;
                    }

                    case 6: //watering plants
                    cout << "Watering plants..." << endl;
                    if (farm[r][c].cropName != "Empty") {
                        Actuator* actuator = &wsc; // base pointer points to WaterSystemControl
                        if (cin.peek() == '\n') {
                            cin.get();
                        }
                        actuator->adjust(farm[r][c].currentWater); // polymorphic call — runs WaterSystemControl::adjust() at runtime
                        actuator = nullptr;// reset pointer after use
                        cout << "Current water level: " << farm[r][c].currentWater << endl;
                    } else {
                        cout << "No crop to water." << endl;
                    }
                    break;

                    case 7: //generate farm logs
                        cout << "Writing logs to file..." << endl;
                        fw.writeLogsToFile(seeder, sprayer, harvester, GlobalTime);
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

int main()
{
    int choice;
    cout << "\nWelcome to SAGE Farm!\n\n";
    cout << "Initializing farm...Please choose from the following options:" << endl;
    cout << "Option 1: View Farm" << endl;
    cout << "Option 2: Generate Output Logs" << endl;
    cout << "Option 3: Exit SAGE Simulator" << endl;
    cout << "Your Option: ";
    cin>>choice;
    while (cin.fail() || choice < 1 || choice > 3) { //error handling
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Please enter a number between 1 and 3: " << endl;
        cin >> choice;
    }
    switch (choice) {
        case 1: //View Farm
            cout << "Viewing farm..." << endl;
            manageFarm(); 
            break;
        case 2: //Write Logs to File
            cout << "Writing logs to file..." << endl;
            fw.writeLogsToFile(seeder, sprayer, harvester, GlobalTime);
            break;
        case 3: //exit program
            cout << "\nExiting SAGE Simulator.\n";
            std::exit(0);
        default: //error
            cout << "Invalid choice. Please enter 1 to view farm or 2 to generate output logs." << endl;
            break;
    } 
  
return 0;        
}