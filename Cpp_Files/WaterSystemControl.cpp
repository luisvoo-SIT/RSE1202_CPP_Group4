#include "WaterSystemControl.h"

void WaterSystemControl::adjustWater(unsigned int &currentWater) 
{
    
    unsigned int newWater; // Declare unsigned int variable for new water level (newWater)
    string input; // string variable to store user input for error handling

    // Prompt user to key in value from 0-10
    cout << "Enter water value (0-10): ";
    getline(cin, input); 

    // While loop for user input error handling 
    while (true) 
    {
        bool allWhitespace = true; // bool variable for allWhitespace() set to true
        getline(cin, input);  // user enter input
        
        // if user input string is empty
        if (input.empty())
        { 
            cout << "Cannot enter an empty value, please enter a value (0-10): ";
            continue; // skip to the start of the while loop
        }
        
        // for loop that iterates through char c from user input
        for (char c : input) 
        {
            if (c != ' ' && (c != '\t' || c!= '\0') ) // if not blank space AND (not tab OR not null character)
            {
                allWhitespace = false;  // set allWhitespace bool variable to false
                break;  // for the while loop
            }
            
        }

        // Check for more than one decimal point
        int dotCount = 0;
        for (char c : input) // for loop that loops through every character in the string variable "input"
        {
            if (c == '.') dotCount++;   // if '.' is encountered, increment the counter by 1
        }

        // if condition for dotCount > 1, prompts user that they keyed in 
        if (dotCount > 1) {
            std::cout << "Invalid input. More than one decimal point detected: ";
            continue;   // skip to the start of the while loop
        }

        // Try to parse the string as a double variable type
        std::istringstream iss(input);      // Creates an istringsteam object initialized with the string variable (i.e input)
        unsigned int parsedValue;                 // declares unsigned int variable called "parsedValue", it holds the user input value if parsing succeeds
        char leftover;                      // declares char variable called "leftover", it holds any unexpected character found after the user input 

        // Try to read double value from stream
        // if not successful, prompt user "Invalid input..."
        if (!(iss >> parsedValue)) {
            std::cout << "Invalid input. Please enter a numeric value: ";
            continue;   // skip to the start of the while loop
        }

        // if have leftover non-numeric characters after the number
        if (iss >> leftover) {
            std::cout << "Invalid input. Unexpected characters after the number: ";
            continue;   // skip to the start of the while loop
        }

        // if parsedValue outside range of (0-10)
        if (parsedValue < 0 || parsedValue > 10) {
            std::cout << "Invalid input. Value must be between 0 and 10: ";
            continue;   // skip to the start of the while loop
        }

        // All checks passed, procceds to assign the parsedValue to newWater
        newWater = parsedValue; // assigns the parsedValue to newWater
        break;  // exits the while loop
        
    }
    
    adjustActuatorLevel(newWater); // updates actuatorLevel in base class Actuator
    currentWater = newWater; // assigns new value (newWater) to current water level (currentWater)

    // Prints updated water level to console
    cout << ">>> Water level has been updated to: " << currentWater << " litres" << endl;




}