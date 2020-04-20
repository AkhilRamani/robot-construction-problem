#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <random>
#include <ctime>
#include <cstdlib>
#include <bits/stdc++.h> 
using namespace std;
#include "implementation.h"

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

// void writeFile(){
//   ofstream outFile;
//   outFile.open();
// }

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

  cout << endl << "\t== CUSTOMER DATA ====" << endl;
  for(auto c:formattedData)
    cout << "\t" << c.name << ",  " << c.order << ",  " << c.parts << endl;

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

  cout << endl << "\t== BUILDER DATA ====" << endl;
  for(auto b: formattedData)
    cout << "\t" << b.name << ",  " << b.ability << ",  " << b.variability << endl;

  return formattedData;
}

vector<part> getPartData(string fileName){
  vector<string> rawData = readFile(fileName);
  vector<part> formattedData;

  for(int i=0; i < rawData.size(); i+=5){
    part p;

    p.code = rawData[i][0];
    p.name = rawData[i+1];
    p.min = stoi(rawData[i+2]);
    p.max = stoi(rawData[i+3]);
    p.complexity = stoi(rawData[i+4]);

    formattedData.push_back(p);
  }

  cout << endl << "\t== PARTS DATA ====" << endl;
  for(auto p:formattedData)
    cout << "\t" << p.code << ",  " << p.name << ",  " << p.min << ",  " << p.max << ",  " << p.complexity << endl;

  return formattedData;
}


int genRandomNo(){
  random_device device;
  mt19937 gen(device());
  uniform_int_distribution<> uniform(0, 2);
  return uniform(gen);
  // return rand()%10;
}

int genRobotComplexity(string robotParts, vector<part> allParts){
  int partComplexity = 0;

  for(auto p : robotParts){
    vector<part>::iterator i = std::find_if(allParts.begin(), allParts.end(), [p](part const& part){
      return part.code == p;
    });
    if(i != allParts.end())
      partComplexity += i -> complexity;
    else
      cerr << "part not found" << endl;
  }

  int complexity = 20 + partComplexity;
  return complexity > 100 ? 100 : complexity;
}

int genRobotVariablity(string robotParts, int builderVariability){
  return 5 + robotParts.length() + builderVariability;
}

int genNormalRandomValue(int builderAbility, int robotVariability){
  default_random_engine randEngine(rand());
  normal_distribution<double> normal(builderAbility, robotVariability);

  return normal(randEngine);
}

bool isBuildSuccessful(int randomValue, int robotComplexity){
  return randomValue >= robotComplexity ? true : false;
}

void build(builder b, customer c, vector<part> parts){
  int robotVariability = genRobotVariablity(c.parts, b.variability);
  int robotComplexity = genRobotComplexity(c.parts, parts);

  cout << "Robot variability: " << robotVariability << endl;
  cout << "Robot Complexity: " << robotComplexity << "\n" << endl;

  bool buildNotSuccess = true;
  int attemptCountOffset = 0;

  while(buildNotSuccess){
    if(attemptCountOffset == 5){
      cout << "attempting the build second time." << endl;

    }
    if(attemptCountOffset == 10){
      cout << "attempting the build third time." << endl;
    }

    int randomValue = genNormalRandomValue(b.ability, robotVariability);
    cout << "Normal random value: " << randomValue << endl;

    if(isBuildSuccessful(randomValue + attemptCountOffset, robotComplexity)){
      cout << "build successful" << endl;
      buildNotSuccess = false;
    }
    else{
      cout << "build failed" << endl;
      attemptCountOffset += 5;
      if(attemptCountOffset > 10) buildNotSuccess = false;
    }
  }
}