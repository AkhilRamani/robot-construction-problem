#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <random>
#include <ctime>
#include <cstdlib>
using namespace std;

#include "implementation.h"

// struct customer{
//   string name;
//   string order;
//   string parts;
// };
// struct builder{
//   string name;
//   int ability;
//   int variability;
// };
// struct part{
//   string code;
//   string name;
//   int min;
//   int max;
//   int complexity;
// };

vector<string> readFile(string fileName){
  ifstream inputFile;
  vector<string> fileData;
  inputFile.open(fileName);

  //reading the input file
  if(inputFile.fail()) cerr << " failed to open" << fileName << endl;   //displays the file opening error

  while(inputFile){
    string line;

    if(!getline(inputFile, line)) break;

    int idx = line.find(".");
    if(idx != -1) line = line.substr(0, idx);                 //removes the "." from the end of a line

    istringstream lineStream(line);

    while (lineStream){
      string subString;
      if(!getline(lineStream, subString, ':')) break;         //breaking the string by ":"
      fileData.push_back(subString);
    }
  }
  inputFile.close();

  return fileData;                                            //returns the string vector
}


vector<customer> getCustomerData(string fileName){
  vector<string> rawData = readFile(fileName);
  vector<customer> formattedData;

  for(int i = 0; i < rawData.size(); i+=3){
    customer c;

    c.name = rawData[i];
    c.order = rawData[i+1];
    c.parts = rawData[i+2];

    formattedData.push_back(c);
  }
  return formattedData;
}

vector<builder> getBuilderData(string fileName){              //function returns vector of builders
  vector<string> rawData = readFile(fileName);                //reads data from file and returns array
  vector<builder> formattedData;  

  for(int i = 0; i < rawData.size(); i+=3){                   //ctrates a vector of builder struct
    builder b;

    b.name = rawData[i];
    b.ability = stoi(rawData[i+1]);
    b.variability = stoi(rawData[i+2]);

    formattedData.push_back(b);
  }
  return formattedData;
}

vector<part> getPartData(string fileName){
  vector<string> rawData = readFile(fileName);
  vector<part> formattedData;

  for(int i=0; i < rawData.size(); i+=5){
    part p;

    p.code = rawData[i];
    p.name = rawData[i+1];
    p.min = stoi(rawData[i+2]);
    p.max = stoi(rawData[i+3]);
    p.complexity = stoi(rawData[i+4]);

    formattedData.push_back(p);
  }
  return formattedData;
}


int genRandomNo(){
  // uniform_int_distribution<int> uniform(0,2);
  // default_random_engine randEngine(time(0));
  // return uniform(randEngine);
  return rand();
}