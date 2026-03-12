#include "Header_Files/Crops.h"
#include <iostream>
using namespace std;

// Function declared in Crops.cpp - for testing
void testUserInput();

int main() {
    cout << "=== Testing Crops User Input Function ===" << endl;
    cout << "\nThis will test the UserInputLoad() function.\n";
    cout << "Make sure 'Crop_Info.csv' exists or be ready to enter a filename.\n\n";
    
    // Call the user input function
    vector<Crop> crops = UserInputLoad();
    
    cout << "\n=== Test Summary ===" << endl;
    cout << "Total crops loaded: " << crops.size() << endl;
    
    if (crops.size() > 0) {
        cout << "\nFirst crop details:\n";
        crops[0].display();
        cout << "User input test: SUCCESS!\n";
    } else {
        cout << "Warning: No crops were loaded.\n";
    }
    
    return 0;
}
