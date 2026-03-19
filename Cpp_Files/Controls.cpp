#include "Header_Files/Controls.h"

// ── Shared helper: handles all the input validation logic ──────────────────
// Returns a valid unsigned int within [0, max], re-prompting on bad input.
static unsigned int getValidInput(const string &prompt, unsigned int max)
{
    string input;
    cout << prompt;   // print the prompt passed in (e.g. "Enter water value (0-10): ")

    while (true)
    {
        getline(cin, input);

        if (input.empty())
        {
            cout << "Cannot enter an empty value, please try again: ";
            continue;
        }

        // Count decimal points — more than one is invalid (in case we want to implement float variable in future)
        int dotCount = 0;
        for (char c : input) if (c == '.') dotCount++;
        if (dotCount > 1)
        {
            cout << "Invalid input. More than one decimal point detected: ";
            continue;
        }

        istringstream iss(input);
        unsigned int parsedValue;
        char leftover;

        if (!(iss >> parsedValue))      // fails if input isn't numeric
        {
            cout << "Invalid input. Please enter a numeric value: ";
            continue;
        }

        if (iss >> leftover)            // fails if there are trailing characters
        {
            cout << "Invalid input. Unexpected characters after the number: ";
            continue;
        }

        if (parsedValue > max)      // fails if user enter exceed max value
        {
            cout << "Invalid input. Value must be between 0 and " << max << ": ";
            continue;
        }

        return parsedValue;     // all checks passed — return the clean value
    }
}

// WaterSystemControl
void WaterSystemControl::adjust(unsigned int &currentValue)
{
    unsigned int newVal = getValidInput("Enter water value (0-10): ", 10); //max water value allowed is set to 10
    adjustActuatorLevel(newVal);    // updates actuatorLevel in base class
    currentValue = newVal;
    cout << ">>> Water level has been updated to: " << currentValue << " litres" << endl;
}

// TempControl
void TempControl::adjust(unsigned int &currentValue)
{
    unsigned int newVal = getValidInput("Enter temperature value (0-50): ", 50); //max temperature value allowed is set to 50
    adjustActuatorLevel(newVal);    // updates actuatorLevel in base class
    currentValue = newVal;
    cout << ">>> Temperature has been updated to: " << currentValue << " C" << endl;
}

// HumidityControl
void HumidityControl::adjust(unsigned int &currentValue)
{
    unsigned int newVal = getValidInput("Enter humidity value (0-100): ", 100); //max humidity value allowed is set to 100
    adjustActuatorLevel(newVal);    // updates actuatorLevel in base class
    currentValue = newVal;
    cout << ">>> Humidity has been updated to: " << currentValue << " %" << endl;
}

// UVControl 
void UVControl::adjust(unsigned int &currentValue)
{
    unsigned int newVal = getValidInput("Enter UV value (0-100): ", 100); //max UV value allowed is set to 100
    adjustActuatorLevel(newVal);    // updates actuatorLevel in base class
    currentValue = newVal;
    cout << ">>> UV Light has been updated to: " << currentValue << " %" << endl;
}

