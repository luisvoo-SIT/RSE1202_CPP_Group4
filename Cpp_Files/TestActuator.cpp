/*
// @Ethan this one is to be integrated into Plot.cpp 

#include "WaterSystemControl.h"
#include "TempControl.h"
#include "HumidityControl.h"
#include "UvControl.h"



// @Ethan this one is to be integrated into Plot.cpp 

int main()
{
    system("cls"); // clear console for better readability
    // default environment variables
    float currentWaterlvl = 4.0f;
    float currentTemp = 20.0f; 
    float currentHum = 60.0f; 
    float currentUV = 10.0f;
    
    int choice; // int variable for storing user input for choice of actuator (1-4)
    do
    {
        cout << "\n=== Actuator Control System ===" << endl;
        cout << "Displaying current environment data:" << endl;
        cout << "  Water Level : " << currentWaterlvl << " litres" << endl;
        cout << "  Temperature : " << currentTemp  << " C" << endl;
        cout << "  Humidity    : " << currentHum   << " %" << endl;
        cout << "  UV Light    : " << currentUV    << " units" << endl;

        cout << "\nSelect actuator to adjust:" << endl;
        cout << "  1) Water System Control" << endl;
        cout << "  2) Temperature Control" << endl;
        cout << "  3) Humidity Control" << endl;
        cout << "  4) UV Light Control" << endl;
        cout << "  5) Exit" << endl;
        cout << "\nChoice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                WaterSystemControl wsc;                 // create object of water system control class
                wsc.adjustWater(currentWaterlvl);    // call function to adjust water level
                break;

            }

            case 2:
            { 
                TempControl tc;                 // create object of moisture control class
                tc.adjustTemperature(currentTemp);    // call function to adjust temperature level
                break;

            }

            case 3:
            {
                HumidityControl hc;                 // create object of humidity control class
                hc.adjustHumidity(currentHum);    // call function to adjust humidity level
                break;
            }

            case 4:
            {
                UVControl uv;                 // create object of UV control class
                uv.adjustUV(currentUV);    // call function to adjust UV level
                break;
            }
            
            case 5: 
                cout << "Exiting Actuator Control" << endl;
                break;

            default: 
                cout << "Invalid choice. Please try again (1-5)" << endl;


        }



    }
    
    while (choice !=5);
    
    return 0;
    
    
}


*/
