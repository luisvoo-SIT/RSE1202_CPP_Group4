#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Cpp_Files/Header_Files/Actuators.h"
#include "Cpp_Files/Header_Files/CropsV2.h"
using namespace std;


int main() {
    int option;

    vector<Crop> crops = Crop::loadCrops("Crop_Info.csv");

  cout << "Select your options: " << endl;
  cout << "1. See what vegetables seed are available" << endl;
  cout << "2. Exit" << endl;
  cin >> option; 

switch (option) {
    case 1: {
        cout<<"you selected 1"<<endl;
    for (size_t i = 0; i < crops.size(); ++i) {
        cout << "Crop " << i+1 << "\n";
        // use display method rather than accessing protected name
        crops[i].displaycropsinfo();
    }

        break;
    }

    
    case 2:
        cout<<"you selected 2"<<endl;
        // code to be executed if option == 2
        break;
}   
    default: // no standalone else allowed after switch; handle default earlier or after switch if needed
    {
        cout << "Invalid option selected." << endl;
    }

    return 0;

}
