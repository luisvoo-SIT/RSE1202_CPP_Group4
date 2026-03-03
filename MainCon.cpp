#include <iostream>
#include <fstream> //added so can read file
#include <string>
#include <sstream> //apparently needed for strings

using namespace std;


int main() {
    cout << "S.A.G.E Simulator Group 4" << endl;
    
    // 1. Attempt to open the data file
    ifstream dataFile("Plots.csv");

    // 2. Check if the file opened successfully
    if (!dataFile.is_open()) {
        cerr << "[ERROR] Could not find or open Plots.csv." << endl;
        cerr << "Please ensure the file is in the same folder as this program." << endl;
        return 1; //exit show error code
    }

    cout << "Successfully loaded Plots.csv. Reading data..." << endl;
    cout << "--------------------------------------------------" << endl;

    string currentLine;
    
    // 3. Read the file line-by-line until the end
    while (getline(dataFile, currentLine)) 
    {
        cout << currentLine << endl; 
    }

    // 4. Always close the file when done
    dataFile.close();
    
    cout << "--------------------------------------------------" << endl;
    cout << "File reading complete" << endl;

    return 0; //exit
}
