#include "Crops.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

// Test function to verify user input loading works
void testUserInput() {
    std::cout << "=== Crops User Input Test ===" << std::endl;
    std::vector<Crop> crops = UserInputLoad();
    std::cout << "Test completed successfully!\n";
}