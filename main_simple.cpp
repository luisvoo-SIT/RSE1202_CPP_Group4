#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Header_Files/Actuators.h"
using namespace std;


int main() {
  int option;
  cout << "Select your options: " << endl;
  cout << "1. Enter your plot" << endl;
  cout << "2. Exit" << endl;
  cin >> option; 

switch (option) {
    case 1: {
        cout<<"you selected 1"<<endl;
        Actuator actuator;          // create an actuator instance
        actuator.displayActuatorLevel(); // display its level
        break;
    }
    case 2:
        cout<<"you selected 2"<<endl;
        // code to be executed if option == 2
        break;
}

}
