#include <iostream>
#include <string>
#include <fstream>
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
    Crop(string n, int minH, int maxH, int minT, int maxT, int minUV, int maxUV, int water, int time) 
        : name(n), minHumidity(minH), maxHumidity(maxH), 
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


int main() {
  // Create and open the csv file
  string MyFileName;
  cout << "Enter the name of the CSV file: ";
  cin >> MyFileName;   
  fstream MyFileName;





}

