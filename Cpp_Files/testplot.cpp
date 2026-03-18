#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include "Header_Files/Robots.h" //chee hui's bot functions
//#include "Header_Files/TimeControl.h"
#include "Header_Files/WaterSystemControl.h" //dino water
#include "Header_Files/CropsV2.h" //luis' crop data
//#include "Header_Files/Actuators.h"
#include "Header_Files/plotv2.h"
//#include "Header_Files/time.h" //time variables

using namespace std;

//global variables:
int farmchoice = 0;
WaterSystemControl wsc;
Plot::Status cropstatus;
//SeedingBot sbot; do i need a global variable to make the bots work?

//global vector initialization:
vector<CropData> availableCrops = CropData::loadCrops();
vector<vector<Plot>> farm(3, vector<Plot>(3));

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
                    /*
                    cout << "Crop Name:   " << farm[r][c].cropName << endl;
                    cout << "Temperature: " << farm[r][c].currentTemp << "°C" << endl;
                    cout << "Humidity:    " << farm[r][c].currentHum << "%" << endl;
                    cout << "Water Level: " << farm[r][c].currentWater << endl;
                    cout << "Time Planted: " <<  << " days" << endl;
                    */

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
                                        //cheehui seeding bot
                                        //SeedingBot();
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
                                        //HarvestingBot();
                                        //set plotTime to 0
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
                                    //time++;
                                    //call time skip function
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


int cropstatus (int i, int r, int c) { //need to add time parameter 
    int warning = 0; 
    
    availableCrops[i].getWaterReq(); //get water requirement for specific crop
    if (farm[r][c].currentWater <= (availableCrops[i].getWaterReq() + 5) || (farm[r][c].currentWater > (availableCrops[i].getWaterReq() - 5))) { //if current water level is not within 5 units of water requirement, crop is dying
        warning++;
        cout << "Your crop is dying." << endl;
    }
    else {  
        warning = 0; //reset warning if water level is good
    } 

    //logic for plot statuses
    if (warning == 2) { //if warning reaches 2, crop dies
        return 0;
    }
    else if (farm[r][c].PlotTime < availableCrops[i].getTimeToGrow()) { //if time is less than time to grow, crop is a seedling
        return 1;
    }
    else if (farm[r][c].PlotTime >= availableCrops[i].getTimeToGrow()) { //if time is greater than or equal to time to grow, crop is harvestable
        return 2;
    }
    else cout << "No crop." << endl;  
}

//change function name
int main() {
    manageFarm();
    return 0;
}
