/*
// For testing (if somehow can add display the other actuator subclasses)

#include "Controls.h"

int main() // DisplayActuatorControl()
{
    system("cls"); // clear console for better readability
    // default environment variables
    unsigned int currentWater = 4;
    unsigned int currentTemp = 20; 
    unsigned int currentHum = 60; 
    unsigned int currentUV = 10;
    
    // Base class pointer — can point to ANY of the derived objects above
    Actuator* actuator = nullptr;

    // Pointer to the correct environment variable to update
    // This lets us pass the right variable into adjust() via the base pointer
    unsigned int* targetValue = nullptr;

    //Creating objects for the actuators
    WaterSystemControl wsc;
    TempControl        tc;
    HumidityControl    hc;
    UVControl          uvc; 

    int choice; // int variable for storing user input for choice of actuator (1-4)
    do
    {
        cout << "\n=== Actuator Control System ===" << endl;
        cout << "Displaying current environment data:" << endl;
        cout << "  Water Level : " << currentWater << " litres" << endl;
        cout << "  Temperature : " << currentTemp  << " C" << endl;
        cout << "  Humidity    : " << currentHum   << " %" << endl;
        cout << "  UV Light    : " << currentUV  << " units" << endl;

        cout << "\nSelect actuator to adjust:" << endl;
        cout << "  1) Water System Control" << endl;
        cout << "  2) Temperature Control" << endl;
        cout << "  3) Humidity Control" << endl;
        cout << "  4) UV Light Control" << endl;
        cout << "  5) Exit" << endl;
        cout << "\nChoice: ";
        cin >> choice;
        cin.clear();     // clear error flags
        cin.ignore(numeric_limits<streamsize>::max(),'\n'); // clear input buffer

        switch (choice)
        {
            // Case 1: WaterSystemControl
            case 1:
            {
                actuator = &wsc;           // point base pointer at WaterSystemControl
                targetValue = &currentWater;  // point to the water variable
                break;

            }

            // Case 2: TempControl
            case 2: 
            {
                actuator = &tc;
                targetValue = &currentTemp;
                break;
            }

            // Case 3: HumidityControl
            case 3:
            {
                actuator = &hc;
                targetValue = &currentHum;
                break;
            }

            // Case 4: UVControl
            case 4:
            {
                actuator = &uvc;
                targetValue = &currentUV;
                break;
            }

            // Case 5, exit Actuator Control Display menu
            case 5: 
                cout << "Exiting Actuator Control" << endl;
                break;

            default: 
                cout << "Invalid choice. Please try again (1-5)" << endl;
                //break;

        }

        // If a valid actuator was selected (not Exit or invalid), call adjust() through
        // the base pointer — C++ picks the correct derived class version at runtime
        if (actuator != nullptr && choice != 5)
        {
            actuator->adjust(*targetValue);  // *targetValue dereferences the pointer to pass by reference
            actuator = nullptr;              // reset pointer after each use
            targetValue = nullptr;
        }


    }
    
    while (choice !=5);
    
    return 0;
    
    
}
*/
