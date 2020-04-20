#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
#include "implementation.h"


int main() {

  cout << "\nReading data from file\n" << "--------------------------" << endl;
  vector<customer> customers = getCustomerData("Customers.txt");
  vector<builder> builders = getBuilderData("Builders.txt");
  vector<part> parts = getPartData("Parts.txt");

  // ofstream outFile;
  // outFile.open("Output.txt", ios::trunc);

  cout << "\n\nStarting the processing customer orders\n" << "---------------------------------------" << endl;
  for (auto c : customers){
    int randomN0 = genRandomNo();
    builder selectedBuilder = builders[randomN0];

    cout << "\nProcessing customer: " << c.name << "\nOrder: " << c.order << "\nbuilder assigned: " << selectedBuilder.name << endl;

    build(selectedBuilder, c, parts);
    cout << "-----\n" << endl;
  }

  return 0;
}