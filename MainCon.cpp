#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

struct Crop {
    string name;
    int minHumidity;
    int maxHumidity;
    int minTemp;
    int maxTemp;
    int minUV;
    int maxUV;
    double waterRequirement;
    int timeToGrow;
};

struct Plot {
    int plotNumber;
    string cropName;
    int plantAge;
    string status;
};

vector<Crop> crops;
vector<Plot> plots;

// Function to load Crop_Info.csv
void loadCropInfo() {
    ifstream file("Crop_Info.csv");
    string line;
    
    getline(file, line); // skip header
    
    while (getline(file, line)) {
        stringstream ss(line);
        string value;
        Crop crop;

        getline(ss, crop.name, ',');
        getline(ss, value, ','); crop.minHumidity = stoi(value);
        getline(ss, value, ','); crop.maxHumidity = stoi(value);
        getline(ss, value, ','); crop.minTemp = stoi(value);
        getline(ss, value, ','); crop.maxTemp = stoi(value);
        getline(ss, value, ','); crop.minUV = stoi(value);
        getline(ss, value, ','); crop.maxUV = stoi(value);
        getline(ss, value, ','); crop.waterRequirement = stod(value);
        getline(ss, value, ','); crop.timeToGrow = stoi(value);

        crops.push_back(crop);
    }

    file.close();
}

// Function to load Plots.csv
void loadPlots() {
    ifstream file("Plots.csv");
    string line;

    getline(file, line); // skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string value;
        Plot plot;

        getline(ss, value, ','); plot.plotNumber = stoi(value);
        getline(ss, plot.cropName, ',');
        getline(ss, value, ','); plot.plantAge = stoi(value);
        getline(ss, plot.status, ',');

        plots.push_back(plot);
    }

    file.close();
}

// Find crop info by name
Crop* findCrop(string name) {
    for (auto &crop : crops) {
        if (crop.name == name)
            return &crop;
    }
    return nullptr;
}

// Display 3x3 grid
void displayGrid() {
    cout << "\nWelcome to SAGE Farm!\n\n";

    for (int i = 0; i < 9; i++) {
        cout << setw(4) << plots[i].plotNumber;
        if ((i + 1) % 3 == 0)
            cout << endl;
    }
}

int main() {

    loadCropInfo();
    loadPlots();

    char choice;

    while (true) {

        displayGrid();

        cout << "\nSelect your plot number to view details (Q to quit): ";
        cin >> choice;

        if (choice == 'Q' || choice == 'q')
            break;

        int plotNum = choice - '0';

        if (plotNum < 1 || plotNum > 9) {
            cout << "Invalid selection.\n";
            continue;
        }

        Plot &selectedPlot = plots[plotNum - 1];
        Crop* crop = findCrop(selectedPlot.cropName);

        cout << "\nPlot " << selectedPlot.plotNumber << " details:\n";
        cout << "Crop: " << selectedPlot.cropName << endl;
        cout << "Status: " << selectedPlot.status << endl;
        cout << "Plant Age: " << selectedPlot.plantAge << " months\n";

        if (crop != nullptr) {
            cout << "\nCrop Requirements:\n";
            cout << "Humidity: " << crop->minHumidity << "-" << crop->maxHumidity << endl;
            cout << "Temperature: " << crop->minTemp << "-" << crop->maxTemp << endl;
            cout << "UV: " << crop->minUV << "-" << crop->maxUV << endl;
            cout << "Water Requirement: " << crop->waterRequirement << endl;
            cout << "Time To Grow: " << crop->timeToGrow << " months\n";
        }

        cout << "\nPress H to Harvest, Q to return: ";
        cin >> choice;

        if ((choice == 'H' || choice == 'h') && selectedPlot.status == "Harvest") {
            cout << "\nSUCCESSFULLY HARVESTED.\n";
            selectedPlot.status = "Empty";
            selectedPlot.cropName = "None";
            selectedPlot.plantAge = 0;
        }
    }

    cout << "\nExiting SAGE Simulator.\n";
    return 0;
}
