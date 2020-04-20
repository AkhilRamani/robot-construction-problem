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

//print data on console as well as write on file
void printAndWrite(string s, ofstream &outfile){
  cout << s << endl;
  outfile << s << endl;
}

//reads the file and returns an array of string, which devided by ":"
vector<string> readFile(string fileName, int dataNeedPerRecord){
  ifstream inputFile;
  vector<string> fileData;
  inputFile.open(fileName);

  //validate the file opening error
  if(inputFile.fail()){
    cerr << "\nexception: failed to open" << fileName << endl << endl;
    exit(0);
  }

  //reading the input file
  while(inputFile){
    string line;

    if(!getline(inputFile, line)) break;

    int idx = line.find(".");
    if(idx != -1) line = line.substr(0, idx);              //removes the "." from the end of a line

    istringstream lineStream(line);

    int dataCount = 0;
    while (lineStream){
      string subString;
      if(!getline(lineStream, subString, ':')) break;      //breaking the string by ":"
      fileData.push_back(subString);
      dataCount++;
    }

    if(dataCount != dataNeedPerRecord){                    //checks required data supplied or not
      cerr << endl << "exception: " << fileName << " not formatted properly. It requires " << dataNeedPerRecord << " data per record.\n" << endl;
      exit (0);
    }
  }

  inputFile.close();

  return fileData;                                         //returns the string vector
}

//format and fill customers data in vector of customer struct
vector<customer> getCustomerData(string fileName){
  vector<string> rawData = readFile(fileName, 3);
  vector<customer> formattedData;

  for(int i = 0; i < rawData.size(); i+=3){
    customer c;

    c.name = rawData[i];
    c.order = rawData[i+1];
    c.parts = rawData[i+2];

    formattedData.push_back(c);
  }

  cout << endl << "\tCUSTOMER DATA" << "\n\t-------------" << endl;
  for(auto c:formattedData)
    cout << "\tName: " << c.name << ",  Order: " << c.order << ",  Parts: " << c.parts << endl;

  return formattedData;
}

//format and fill builders data in vector of builder struct
vector<builder> getBuilderData(string fileName){           //function returns vector of builders
  vector<string> rawData = readFile(fileName, 3);          //reads data from file and returns array
  vector<builder> formattedData;  

  for(int i = 0; i < rawData.size(); i+=3){                //ctrates a vector of builder struct
    builder b;

    b.name = rawData[i];
    b.ability = stoi(rawData[i+1]);
    b.variability = stoi(rawData[i+2]);

    formattedData.push_back(b);
  }

  cout << endl << "\tBUILDER DATA" << "\n\t------------" << endl;
  for(auto b: formattedData)
    cout << "\tName: " << b.name << ",  Ability: " << b.ability << ",  Variability: " << b.variability << endl;

  return formattedData;
}

//format and fill parts data in vector of part struct
vector<part> getPartData(string fileName){
  vector<string> rawData = readFile(fileName, 5);
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

  cout << endl << "\tPARTS DATA" << "\n\t----------" << endl;
  for(auto p:formattedData)
    cout << "\tCode: " << p.code << ",  Name: " << p.name << ",  Minimum: " << p.min << ",  Maximum: " << p.max << ",  Complexity: " << p.complexity << endl;

  return formattedData;
}

//generates random number between 0 and 2
int genRandomNo(){
  random_device device;
  mt19937 gen(device());
  uniform_int_distribution<> uniform(0, 2);
  return uniform(gen);
}

int genRobotComplexity(string robotParts, vector<part> allParts){
  int partComplexity = 0;

  for(auto p : robotParts){

    //iterates over parts vector and returns part struct, which code matchs with the variable "p"
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

//generates a random value by normal distribution
int genNormalRandomValue(int builderAbility, int robotVariability){
  default_random_engine randEngine(rand());
  normal_distribution<double> normal(builderAbility, robotVariability);
  return normal(randEngine);
}

//fun returns true if build success, else returns flase
bool isBuildSuccessful(int randomValue, int robotComplexity){
  return randomValue >= robotComplexity ? true : false;
}

//actual build logic for building robot
void build(builder b, customer c, vector<part> parts, ofstream &outfile){
  int robotVariability = genRobotVariablity(c.parts, b.variability);
  int robotComplexity = genRobotComplexity(c.parts, parts);

  printAndWrite("Overall robot variability: " + to_string(robotVariability), outfile);
  printAndWrite("Overall robot complexity: " + to_string(robotComplexity), outfile);

  bool buildNotSuccess = true;
  int attemptCountOffset = 0;

  while(buildNotSuccess){        //loop keeps running untill build successeds

    if(attemptCountOffset == 5) printAndWrite("attempting the build second time", outfile);
    if(attemptCountOffset == 10) printAndWrite("attempting the build third time", outfile);

    int randomValue = genNormalRandomValue(b.ability, robotVariability);
    printAndWrite("Normal random value: " + to_string(randomValue), outfile);

    if(isBuildSuccessful(randomValue + attemptCountOffset, robotComplexity)){
      printAndWrite("build successful", outfile);
      buildNotSuccess = false;        //now build completed. So, buildNotSuccess = false stops while loop 
    }
    else{
      printAndWrite("build failed", outfile);
      attemptCountOffset += 5;
      if(attemptCountOffset > 10) buildNotSuccess = false;        //forcefully stops build loop, because 3 attempts done
    }
  }
}