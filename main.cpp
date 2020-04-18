#include <iostream>
#include <iomanip>
#include <string>
// #include <map>
// #include <random>
// #include <ctime>
// #include <fstream>
// #include <sstream>
#include <vector>
using namespace std;
#include "implementation.h"


int main() {

  cout << endl << "=== CUSTOMER DATA ===" << endl;
  vector<customer> customers = getCustomerData("Customer.txt");
  for(auto c:customers)
    cout << c.name << " " << c.order << " " << c.parts << endl;

  cout << endl << "=== BUILDER DATA ===" << endl;
  vector<builder> builders = getBuilderData("Builders.txt");
  for(auto b: builders)
    cout << b.name << "  " << b.ability << "  " << b.variability << endl;

  cout << endl << "=== PARTS DATA ===" << endl;
  vector<part> parts = getPartData("Parts.txt");
  for(auto p:parts)
    cout << p.code << "  " << p.name << "  " << p.min << "  " << p.max << "  " << p.complexity << endl;

  cout << endl << "random no: " << genRandomNo() << endl;

  return 0;
}