#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class Crop {
private:
    string name;
    int minHumidity;
    int maxHumidity;
    int minTemperature;
    int maxTemperature;
    int minUVIntensity;
    int maxUVIntensity;
    int waterRequirement;
    int timeToGrow;

public:
    // Constructor
    Crop(string n, int minH, int maxH,
         int minT, int maxT,
         int minUV, int maxUV,
         int water, int time)
        : name(move(n)),
          minHumidity(minH), maxHumidity(maxH),
          minTemperature(minT), maxTemperature(maxT),
          minUVIntensity(minUV), maxUVIntensity(maxUV),
          waterRequirement(water), timeToGrow(time) {}

    void display() const {
        cout << "Crop: " << name << "\n"
             << "Humidity: " << minHumidity << "-" << maxHumidity << "%\n"
             << "Temperature: " << minTemperature << "-" << maxTemperature << "°C\n"
             << "UV Intensity: " << minUVIntensity << "-" << maxUVIntensity << "\n"
             << "Water Requirement: " << waterRequirement << "\n"
             << "Time to Grow: " << timeToGrow << " months\n"
             << "------------------------\n";
    }
    
    string getName() const { return name; }
};

// helper to load crops from a CSV file
vector<Crop> loadCrops(const string &filename) {
    vector<Crop> crops;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Unable to open file '" << filename << "'\n";
        return crops;
    }

    string line;
    // skip header
    if (!getline(file, line))
        return crops;

    while (getline(file, line)) {
        if (line.empty())
            continue;
        stringstream ss(line);
        string name;
        double minH, maxH, minT, maxT, minUV, maxUV, water, time;
        char comma;
        if (getline(ss, name, ',') &&
            ss >> minH >> comma >> maxH >> comma
               >> minT >> comma >> maxT >> comma
               >> minUV >> comma >> maxUV >> comma
               >> water >> comma >> time) {
            crops.emplace_back(name, minH, maxH, minT, maxT, minUV, maxUV, water, time);
        }
    }
    return crops;
}

int main() {
    // read filename from user or use default
    string filename;
    cout << "Enter the name of the CSV file (or press Enter to use default): ";
    getline(cin, filename);
    if (filename.empty())
        filename = "Crop_Info.csv";

    vector<Crop> crops = loadCrops(filename);
    cout << "Loaded " << crops.size() << " crops.\n";
    for (const auto &c : crops)
        c.display();

    return 0;
}

