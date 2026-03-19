#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <limits>

// robot headers
#include "Cpp_Files/Header_Files/Robots.h"
#include "Cpp_Files/Header_Files/seedingBot.h"
#include "Cpp_Files/Header_Files/SprayerBot.h"
#include "Cpp_Files/Header_Files/HarvestBot.h"

// time
#include "Cpp_Files/Header_Files/time.h"

// actuators
#include "Cpp_Files/Header_Files/WaterSystemControl.h"
#include "Cpp_Files/Header_Files/Actuators.h"

// crop data
#include "Cpp_Files/Header_Files/CropsV2.h"

// plot
#include "Cpp_Files/Header_Files/plotv2.h"

// file writer
#include "Cpp_Files/Header_Files/FileWriter.h"

using namespace std;

// ── global variables ──────────────────────────────────────────
int farmchoice = 0;
int GlobalTime = 0;

// ── initialise objects ────────────────────────────────────────
WaterSystemControl wsc;
TimeControl        advancePlotTime;

// ── load crops and initialise robots ─────────────────────────
vector<CropData>       availableCrops = CropData::loadCrops();
vector<vector<Plot>>   farm(3, vector<Plot>(3));
SeedingBot             seeder("S01", availableCrops[0]);
HarvestingBot          harvester("H01");
SprayerBot             sprayer("SP01", 100.0, 0.5);     // ← uncommented

// ── display the 3x3 farm grid ─────────────────────────────────
void displayFarm(const vector<vector<Plot>>& farm) {
    cout << "\n--- VERTICAL FARM 3x3 SECTOR GRID ---" << endl;

    for (int i = 0; i < 3; i++) {
        for (int spaceRow = 0; spaceRow < 3; spaceRow++) {
            for (int j = 0; j < 3; j++) {
                for (int spaceCol = 0; spaceCol < 3; spaceCol++) {
                    cout << "[" << farm[i][j].symbol << "]";
                }
                if (j < 2) cout << " | ";
            }
            cout << endl;
        }
        if (i < 2)
            cout << "-----------------------+-----------------------+-----------------------" << endl;
    }
}

int main() {
    cout << "========================================\n"
         << "      Welcome to the Vertical Farm\n"
         << "========================================\n\n";

    // ── check crops loaded ────────────────────────────────────
    if (availableCrops.empty()) {
        cout << "Error: no crops loaded. Check your CSV file.\n";
        return 1;
    }
    cout << "Crops loaded: " << availableCrops.size() << "\n";

    int choice = 0;

    while (choice != 2) {
        displayFarm(farm);
        cout << "\n1. View Plot\n2. Exit\n   Choice: ";
        cin  >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            int plotId;

            while (true) {
                cout << "\nEnter Plot ID to view (1-9) or 0 to return: ";

                if (!(cin >> plotId)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a number between 1 and 9.\n";
                    continue;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (plotId == 0) {
                    cout << "Returning to menu...\n";
                    break;
                }

                if (plotId < 1 || plotId > 9) {
                    cout << "Invalid Plot ID. Please enter between 1 and 9.\n";
                    continue;
                }

                // ── convert plot ID to row and col ────────────
                int r = (plotId - 1) / 3;
                int c = (plotId - 1) % 3;

                cout << "\n===============================\n"
                     << "      VIEWING PLOT ID: " << plotId << "\n"
                     << "===============================\n";

                // ── display plot visual ───────────────────────
                for (int i = 0; i < 3; i++) {
                    cout << "       ";
                    for (int j = 0; j < 3; j++)
                        cout << "[" << farm[r][c].symbol << "]";
                    cout << "\n";
                }

                // ── display plot metadata ─────────────────────
                cout << "-------------------------------\n"
                     << "Crop Name:    " << farm[r][c].cropName                           << "\n"
                     << "Crop Status:  " << farm[r][c].StatusNames[farm[r][c].cropstatus] << "\n"
                     << "Temperature:  " << farm[r][c].currentTemp                        << " C\n"
                     << "Humidity:     " << farm[r][c].currentHum                         << " %\n"
                     << "Water Level:  " << farm[r][c].currentWater                       << "\n"
                     << "Time Planted: " << farm[r][c].PlotTime                           << " days\n"
                     << "-------------------------------\n";

                cout << "Press Enter to continue...";
                cin.get();

                bool inPlotMenu = true;
                while (inPlotMenu) {
                    cout << "\nPlease select an option:\n"
                         << "1. Plant new crop\n"
                         << "2. Harvest crop\n"
                         << "3. Apply Pesticide\n"
                         << "4. View Other Plots\n"
                         << "5. Skip the Day\n"
                         << "6. Water Plants\n"
                         << "7. Return to Main Menu\n\n"
                         << "Select Your Option: ";
                    cin >> farmchoice;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    if (cin.fail() || farmchoice < 1 || farmchoice > 7) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid option. Try again.\n";
                        continue;
                    }

                    switch (farmchoice) {
                        case 1: {
                            // ── plant new crop ────────────────
                            cout << "Planting new crop...\n";
                            if (farm[r][c].cropName == "Empty") {
                                CropData plant = seeder.plantSeeds(1, availableCrops);
                                farm[r][c].cropName   = plant.getName();
                                farm[r][c].cropstatus = Plot::Status::SEED;
                                cout << "\n=== Selected Crop Data ===\n"
                                     << "  Crop         : " << plant.getName()       << "\n"
                                     << "  Time to Grow : " << plant.getTimeToGrow() << " days\n"
                                     << "  Water/day    : " << plant.getWaterReq()   << " mL\n"
                                     << "  Humidity     : " << plant.getMinHum()
                                                            << " - " << plant.getMaxHum()  << " %\n"
                                     << "  Temperature  : " << plant.getMinTemp()
                                                            << " - " << plant.getMaxTemp() << " C\n"
                                     << "  UV Intensity : " << plant.getMinUV()
                                                            << " - " << plant.getMaxUV()   << "\n";
                            } else {
                                cout << "Plot already has a crop.\n";
                            }
                            break;
                        }

                        case 2: {
                            // ── harvest crop ──────────────────
                            cout << "Harvesting crop...\n";
                            if (farm[r][c].cropName != "Empty") {
                                Plot::Status status = static_cast<Plot::Status>(farm[r][c].cropstatus);
                                harvester.evaluateAndHarvest(availableCrops[0], status);

                                // ── reset plot ────────────────
                                farm[r][c].cropstatus   = Plot::Status::EMPTY;
                                farm[r][c].PlotTime     = 0;
                                farm[r][c].currentWater = 0;
                                farm[r][c].currentTemp  = 20.0;
                                farm[r][c].currentHum   = 60.0;
                                farm[r][c].cropName     = "Empty";
                            } else {
                                cout << "No crop to harvest.\n";
                            }
                            break;
                        }

                        case 3: {
                            // ── apply pesticide ───────────────
                            cout << "Applying pesticide...\n";
                            if (farm[r][c].cropName != "Empty") {
                                string chemical = sprayer.sprayArea(10.0);  // ← sprayer used here
                                if (!chemical.empty())
                                    cout << "Applied: " << chemical << "\n";
                            } else {
                                cout << "No crop to apply pesticide.\n";
                            }
                            break;
                        }

                        case 4: {
                            // ── view other plots ──────────────
                            cout << "Returning to plot selection...\n";
                            inPlotMenu = false;     // ← exit inner loop
                            break;
                        }

                        case 5: {
                            // ── skip the day ──────────────────
                            cout << "Skipping day...\n";

                            if (farm[r][c].cropName == "Empty") {
                                cout << "No crop in this plot.\n";
                                break;
                            }

                            int warning = 0;
                            double waterReq = availableCrops[0].getWaterReq();

                            if (farm[r][c].currentWater > waterReq + 5 ||
                                farm[r][c].currentWater < waterReq - 5) {
                                warning++;
                                cout << "Your crop is dying!\n"
                                     << "Water required: " << waterReq                   << "\n"
                                     << "Current water : " << farm[r][c].currentWater    << "\n";
                            } else {
                                warning = 0;
                            }

                            // ── update plot status ────────────
                            if (warning >= 2) {
                                farm[r][c].cropstatus = Plot::Status::DEAD;
                                cout << "Crop has died.\n";
                            } else if (farm[r][c].PlotTime < availableCrops[0].getTimeToGrow()) {
                                farm[r][c].cropstatus = Plot::Status::SEED;
                                cout << "Crop is still growing.\n";
                            } else {
                                farm[r][c].cropstatus = Plot::Status::PLANT;
                                cout << "Crop is ready to harvest!\n";
                            }

                            farm[r][c].PlotTime++;
                            farm[r][c].currentWater -= waterReq;

                            cout << "Day       : " << farm[r][c].PlotTime     << "\n"
                                 << "Water     : " << farm[r][c].currentWater << "\n"
                                 << "Status    : " << farm[r][c].StatusNames[farm[r][c].cropstatus] << "\n";
                            break;
                        }

                        case 6: {
                            // ── water plants ──────────────────
                            cout << "Watering plants...\n";
                            if (farm[r][c].cropName != "Empty") {
                                wsc.adjustWater(farm[r][c].currentWater);
                            } else {
                                cout << "No crop to water.\n";
                            }
                            break;
                        }

                        case 7: {
                            // ── return to main menu ───────────
                            cout << "Returning to main menu...\n";
                            inPlotMenu = false;     // ← exit inner loop
                            break;
                        }

                        default:
                            break;
                    }
                }
                break;
            }
        }

        else if (choice == 2) {
            cout << "Exiting farm...\n";
        }

        else {
            cout << "Invalid choice. Please enter 1 or 2.\n";
        }
    }

    // ── write logs to file after farm is done ─────────────────
    cout << "\n=== Generating Farm Report ===\n";
    writeLogsToFile(seeder, sprayer, harvester);

    cout << "\n========================================\n"
         << "         Thank you for farming!\n"
         << "========================================\n";

    return 0;
}
/*

---

What changed from the original:
```
manageFarm()         → removed, code moved into main()
int main()           → now contains all the farm logic
SprayerBot           → uncommented, used in case 3
inPlotMenu bool      → added to control inner while loop
                       instead of break which only broke
                       the switch not the while loop
warning variable     → moved inside case 5 scope
                       fixes crosses initialization error
writeLogsToFile()    → called at the end of main()
                       after the farm loop exits
cin.ignore()         → added after every cin >> 
                       fixes double input issue
Plot::Status::EMPTY  → used in case 2 reset
Plot::Status::DEAD   → used in case 5 status update
*/
