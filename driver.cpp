#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
#include "implementation.h"


int main(int argc, char* argv[]) {

  if(argc != 5){
    cerr << "\nrun command is not provided properly. Please check in readme.txt file to know how to run and compile\n" << endl;
    return 0;
  }

  cout << "\nReading data from file\n" << "----------------------" << endl;
  vector<customer> customers = getCustomerData(argv[1]);      //reads customer data
  vector<part> parts = getPartData(argv[2]);                  //reads part data
  vector<builder> builders = getBuilderData(argv[3]);         //reads builder data

  ofstream outFile;
  outFile.open(argv[4], ios::trunc);                          //opens output file stream in truncate mode

  cout << "\n\nStarting the processing customer orders\n" << "---------------------------------------" << endl;

  for (auto c : customers){

    int randomNo = genRandomNo();
    builder selectedBuilder = builders[randomNo];             //selects a builder from builders vector by random number between 0 and 2

    printAndWrite("Processing customer: " + c.name + "\nOrder: " + c.order + "\nBuilder assigned: " + selectedBuilder.name, outFile);

    build(selectedBuilder, c, parts, outFile);                //starts build process for a perticulat customer

    printAndWrite("-----\n", outFile);
    cout << endl;
  }

  return 0;
}