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

//file writer
#include "Header_Files/FileWriter.h"

using namespace std;
void manageFarm(); 
//initialize objects
Plot plot;
//writeLogsToFile log;

int main()
{
    int choice;
    cout << "\nWelcome to SAGE Farm!\n\n";
    cout << "Initializing farm... choose an option: ";
    cin>>choice;
    switch (choice) {
        case 1: 
            //View Farm
            cout << "Viewing farm..." << endl;
            manageFarm(); 
            break;
            
        case 2:
            //Write Logs to File
            cout << "Writing logs to file..." << endl;
            //writeLogsToFile(seeder, sprayer, harvester);
            break;
        
        case 3:
            cout << "\n Exiting SAGE Simulator.\n";
            break;

        default:
            cout << "Invalid choice. Please enter 1 to view farm or 2 to return to main menu." << endl;
            break;
    }       
    
   /*
   1. insert csv
   2. gui - plots, output file, quit
   
   */
}
