#include "Controls.h"

void WaterSystemControl::adjustWater(unsigned int &currentWater)
{
    unsigned int newWater; // Declare unsigned int variable for new water level (newWater)
    string input;   // string variable to store user input for error handling

    // Prompt user to key in value from 0-10
    cout << "Enter water value (0-10): ";
    getline(cin, input);

    // While loop for user input error handling
    while (true)
    {
        getline(cin, input);

        // if user input string is empty
        if (input.empty())
        {
            cout << "Cannot enter an empty value, please enter a value (0-10): ";
            continue;   // skip to the start of the while loop
        }

        // Check for more than one decimal point
        int dotCount = 0;
        for (char c : input)    // for loop that loops through every character in the string variable "input"
        {
            if (c == '.') dotCount++;   // if '.' is encountered, increment the counter by 1
        }

        // if condition for dotCount > 1, prompts user that they keyed in 
        if (dotCount > 1)
        {
            cout << "Invalid input. More than one decimal point detected: ";
            continue;   // skip to the start of the while loop
        }

        // Try to parse the string as a unsigned int variable type
        istringstream iss(input);   // Creates an istringsteam object initialized with the string variable (i.e input)
        unsigned int parsedValue;   // declares unsigned int variable called "parsedValue", it holds the user input value if parsing succeeds
        char leftover;              // declares char variable called "leftover", it holds any unexpected character found after the user input 

        // Try to read unsigned int value from stream
        // if not successful, prompt user "Invalid input..."
        if (!(iss >> parsedValue))
        {
            cout << "Invalid input. Please enter a numeric value: ";
            continue;   // skip to the start of the while loop
        }

         // if have leftover non-numeric characters after the number
        if (iss >> leftover)
        {
            cout << "Invalid input. Unexpected characters after the number: ";
            continue;
        }

        // if parsedValue more > 10
        if (parsedValue > 10)
        {
            cout << "Invalid input. Value must be between 0 and 10: ";
            continue;   // skip to the start of the while loop
        }

        // All checks passed, procceds to assign the parsedValue to newWater
        newWater = parsedValue; // assigns the parsedValue to newWater
        break;   // exits the while loop
    }

    adjustActuatorLevel(newWater);  // updates actuatorLevel in base class Actuator
    currentWater = newWater;    // assigns new value (newWater) to current water level (currentWater)

    // Prints updated water level to console
    cout << ">>> Water level has been updated to: " << currentWater << " litres" << endl;

}

// ============================================================
// TempControl — To be implemented
// ============================================================
void TempControl::adjustTemperature(unsigned int &currentTemp)
{
    // TO DO: implement
}

// ============================================================
// HumidityControl — To be implemented
// ============================================================
void HumidityControl::adjustHumidity(unsigned int &currentHum)
{
    // TO DO: implement
}

// ============================================================
// UVControl — To be implemented
// ============================================================
void UVControl::adjustUV(unsigned int &currentUV)
{
    // TO DO: implement
}