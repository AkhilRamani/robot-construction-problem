struct customer{
  string name;
  string order;
  string parts;
};
struct builder{
  string name;
  int ability;
  int variability;
};
struct part{
  char code;
  string name;
  int min;
  int max;
  int complexity;
};

void printAndWrite(string s, ofstream &outfile);
vector<string> readFile(string fileName, int dataNeedPerRecord);
vector<customer> getCustomerData(string fileName);
vector<builder> getBuilderData(string fileName);
vector<part> getPartData(string fileName);
int genRandomNo();
int genRobotComplexity(string robotParts, vector<part> allParts);
int genRobotVariablity(string robotParts, int builderVariability);
int genNormalRandomValue(int builderAbility, int robotVariability);
void build(builder b, customer c, vector<part> parts, ofstream &outfile);