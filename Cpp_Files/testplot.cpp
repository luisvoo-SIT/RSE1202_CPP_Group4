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

//global time function
#include "Header_Files/time.h"

//actuator functions
#include "Header_Files/WaterSystemControl.h" //dino water
#include "Header_Files/Actuators.h"

//crop data functions
#include "Header_Files/CropsV2.h" //luis' crop data

//plot functions
#include "Header_Files/plotv2.h"

using namespace std;

//global variables:
int farmchoice = 0;
int GlobalTime = 0; //how long farm has been running for

//things to initialize:
WaterSystemControl wsc;
Plot::Status cropstatus (int i, int r, int c);
string seedbotname = "S01";
 // Initialize with default crop, will be updated when user plants
HarvestingBot harvester ("H01"); //harvest bot initialization
// SprayerBot sprayer ("P01"); //sprayer bot initialization
TimeControl advancePlotTime; //time control initialization (plot only)

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

void manageFarm() {

    int choice = 0;

    while (choice != 8) {
        displayFarm(farm);
        cout << "\n1. View Plot\n2. Return to Main Menu\n   Choice: ";
        cin >> choice;

        if (choice == 1) {
            int plotId;

            while (true) {
                cout << "\nEnter Plot ID to view (1-9) or 0 to return: ";
                
                if (!(cin >> plotId)) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid input. Please enter a number between 1 and 9 (or 0 to return)." << endl;
                    continue;
                }

                if (plotId == 0) {
                    cout << "Returning to menu..." << endl;
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
                        cout << "       "; // Indent for looks
                        for (int j = 0; j < 3; j++) {
                            cout << "[" << farm[r][c].symbol << "]";
                        }
                        cout << endl;
                    }

                    // Display the metadata -- override w chee hui's
                    cout << "-------------------------------" << endl;
                    
                    cout << "Crop Name:   " << farm[r][c].cropName << endl;
                    cout << "Crop Status: " << farm[r][c].StatusNames[farm[r][c].cropstatus] << endl;
                    cout << "Temperature: " << farm[r][c].currentTemp << "°C" << endl;
                    cout << "Humidity:    " << farm[r][c].currentHum << "%" << endl;
                    cout << "Water Level: " << farm[r][c].currentWater << endl;
                    cout << "Time Planted: " << farm[r][c].PlotTime << " days" << endl;
                    

                    //add day, global day variable
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
                        cout << "6. Water Plants" << endl;
                        cout << "7. Return to Main Menu" << endl << endl;
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
                            switch (farmchoice)
                            {
                                case 1: //call planting robot
                                    cout << "planting new crop" << endl;
                                    //plantrobot();
                                    //manageFarm();
                                    if (farm[r][c].cropName == "Empty"){ //if (farm[r][c].cropName != "Empty") - replace current statement w this once seeding bot is working:
                                        cout << "we need da plant" << endl;
                                        CropData plant = seeder.plantSeeds(1, availableCrops);  //to store the returned object into the array
                                        farm[r][c].cropName = plant.getName();
                                        // ── Access all crop data through the returned object ──────────
                                        cout << "\n=== Selected Crop Data ===\n"
                                            << "  Crop         : " << plant.getName()             << "\n"
                                            << "  Time to Grow : " << plant.getTimeToGrow()       << " days\n"
                                            << "  Water/day    : " << plant.getWaterReq()<< " mL\n"
                                            << "  Humidity     : " << plant.getMinHum()
                                            << " - " << plant.getMaxHum() << " %\n"
                                            << "  Temperature  : " << plant.getMinTemp()
                                            << " - " << plant.getMaxTemp() << " C\n"
                                            << "  UV Intensity : " << plant.getMinUV()
                                            << " - " << plant.getMaxUV() << "\n";
                                        farm[r][c].cropstatus = Plot::Status::SEED; //set plot status to seed
                                        //initialize time object, and run the plotTime ++ function
                                    }
                                    else{
                                        cout << "Plot already has a crop." << endl;
                                    }
                                    break;
                                case 2: //call harvesting robot 
                                    cout << "harvest da crop" << endl;
                                   if (farm[r][c].cropName != "Empty"){ 
                                        cout << "take me" << endl;
                                        //cheehui harvest bot;

                                        
                                        farm[r][c].cropstatus = Plot::Status::EMPTY; //plot status now empty
                                        //reset plot to default values
                                        farm[r][c].PlotTime = 0;
                                        farm[r][c].currentWater = 0;
                                        farm[r][c].currentTemp = 20.0;
                                        farm[r][c].currentHum = 60.0;
                                        farm[r][c].currentWater = 0;
                                        farm[r][c].cropName = "Empty";
                                        //plant.setTimeToGrow(0);
                                    }
                                    else{
                                        cout << "No crop to harvest." << endl;
                                    }
                                    break;
                                case 3: //call pesticide robot
                                    cout << "deleting pests" << endl;
                                    if (farm[r][c].cropName != "Empty"){ 
                                        cout << "clean me" << endl;
                                        //cheehui pest bot;
                                        //PesticideBot();
                                    }
                                    else{
                                        cout << "No crop to apply pesticide." << endl;
                                    }     
                                    break;
                                case 4: //viewing other plots
                                    cout << "viewing plots" << endl;                                      
                                    break;
                                case 5: //time skip (x day increments)
                                    cout << "zzzzz" << endl;
                                    int warning;
                                    int i;
                                    
                                    availableCrops[0].getWaterReq(); //get water requirement for specific crop
                                    if (farm[r][c].currentWater > (availableCrops[i].getWaterReq() + 5) || (farm[r][c].currentWater < (availableCrops[i].getWaterReq() - 5))) { //if current water level is not within 5 units of water requirement, crop is dying
                                        warning++;
                                        cout << "Your crop is dying." << endl;
                                        cout << "water req." << availableCrops[0].getWaterReq() << endl;
                                        cout << "current water." << farm[r][c].currentWater << endl;
                                    }
                                    else {  
                                        warning = 0; //reset warning if water level is good
                                    } 
                                    
                                    //logic for plot statuses
                                    if (warning == 2) { //if warning reaches 2, crop dies
                                        farm[r][c].cropstatus = 2;
                                       
                                    }
                                    else if (farm[r][c].PlotTime < availableCrops[i].getTimeToGrow()) { //if time is less than time to grow, crop is a seedling
                                        farm [r][c].cropstatus = 0;
                                        
                                    }
                                    else if (farm[r][c].PlotTime >= availableCrops[i].getTimeToGrow()) { //if time is greater than or equal to time to grow, crop is harvestable
                                        farm[r][c].cropstatus = 1;
                                        
                                    }
                                    else cout << "No crop." << endl;
                                    //farm[r][c].cropstatus = 3;
                                     
                                    farm[r][c].PlotTime++;
                                    farm[r][c].currentWater -= availableCrops[i].getWaterReq(); //decrease water level by water requirement each day
                                    cout<< endl << farm[r][c].PlotTime <<endl;
                                    cout << farm[r][c].currentWater << endl;
                                    cout<<farm[r][c].cropstatus<<endl;
                                    break;
                                case 6: //watering plants
                                    cout << "feeeeeeeeed" << endl;
                                    if (farm[r][c].cropName != "Empty"){ //if (farm[r][c].cropName != "Empty") - replace current statement w this once seeding bot is working:
                                        cout << "feed me" << endl;
                                        wsc.adjustWater(farm[r][c].currentWater); //dinowater
                                    }
                                    else{
                                        cout << "No crop to water." << endl;
                                    }
                                    break;
                                case 7: //return to main menu
                                    cout << "Returning to main menu..." << endl;
                                    //maincon.cpp
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

//change function name
int main() {
    manageFarm();
    return 0;
}
