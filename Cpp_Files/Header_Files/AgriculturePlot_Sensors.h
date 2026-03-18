#include <iostream>
using namespace std;

class Plot {       // The class
  public:             // Access specifier
    int PlotID,Size;
    enum Plot_Status {Seeded,Vegetative,ReadyToHarvest,Harvested};
    Plot_Status status;  //enum variable
};



