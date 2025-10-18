#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

class definition {
public:
  string name;
  int value;
  definition(string name, int value) {
    this->name = name;
    this->value = value;
  }
};


vector<definition> d;

int findDefinition(string def) {
  for (int i = 0; i<d.size(); i++) {
    char state = 'l';
    if (def.length() >= 4 && def.compare(def.length() - 4, 4, ".Low") == 0) {
      state = 'l';
      def.erase(def.size() - 3, 4);
    } else if (def.length() >= 4 && def.compare(def.length() - 4, 4, ".Mid") == 0) {
      state = 'm';
      def.erase(def.size() - 3, 4);
    } if (def.length() >= 5 && def.compare(def.length() - 5, 5, ".High") == 0) {
      state = 'h';
      def.erase(def.size() - 4, 5);
    }
    if (d[i].name == def) {
      switch (state) {
      case 'l':	return def[i] & 255;
      case 'm':	return (def[i]/256) & 255;
      case 'h': return (def[i]/65536) & 255;
      }
    }
  }
  return 0;
}

void handleDefine(string def) {
  string defName;
  string defValue;
  bool writeSelect = 0;
  for (int i = 0; i < def.size(); i++) {
    if (def[i] != ' ' && !writeSelect) {
      defName += def[i];
    } else {
      defValue += def[i];
      writeSelect = true;
    }
  }
  defValue.erase(0, 1);
  definition temp(defName, stoi(defValue));
  d.push_back(temp);
  return;
}

void handleLabel(string name, int addr) {
  definition temp(name, addr);
  cout<<name<<" "<<addr<<endl;
  d.push_back(temp);
  return;
}


int assembleInstruction(string inst) {
  if (inst == "add") {
    return 0;
  } else if (inst == "sub") {
    return 1;
  } else if (inst == "or") {
    return 2;
  } else if (inst == "nor") {
    return 3;
  } else if (inst == "and") {
    return 4;
  } else if (inst == "nand") {
    return 5;
  } else if (inst == "xor") {
    return 6;
  } else if (inst == "xnor") {
    return 7;
  } else if (inst == "shr") {
    return 8;
  } else if (inst == "biz") {
    return 9;
  } else if (inst == "bnz") {
    return 10;
  } else if (inst == "bic") {
    return 11;
  } else if (inst == "bnc") {
    return 12;
  } else if (inst == "brk") {
    return 63;
  } else return findDefinition(inst);
}

int assembleInput(string in) {
  if (all_of(in.begin(), in.end(), ::isdigit)){
    return stoi(in);
  } else if (in == "r0") {
    return 0;
  } else if (in == "r1") {
    return 1;
  } else if (in == "r2") {
    return 2;
  } else if (in == "r3") {
    return 3;
  } else if (in == "r4") {
    return 4;
  } else if (in == "r5") {
    return 5;
  } else if (in == "r6") {
    return 6;
  } else if (in == "r7") {
    return 7;
  } else if (in == "r8") {
    return 8;
  } else if (in == "r9") {
    return 9;
  } else if (in == "ram") {
    return 10;
  } else if (in == "stk") {
    return 11;
  } else return findDefinition(in);
}

int assembleOutput(string out) {
  if (out == "r0") {
    return 0;
  } else if (out == "r1") {
    return 1;
  } else if (out == "r2") {
    return 2;
  } else if (out == "r3") {
    return 3;
  } else if (out == "r4") {
    return 4;
  } else if (out == "r5") {
    return 5;
  } else if (out == "r6") {
    return 6;
  } else if (out == "r7") {
    return 7;
  } else if (out == "r8") {
    return 8;
  } else if (out == "r9") {
    return 9;
  } else if (out == "ram") {
    return 10;
  } else if (out == "stk") {
    return 11;
  } else return findDefinition(out);
}

char decToHex(int num) {
  char c1;
  switch (num) {
  case 0:  return '0';
  case 1:  return '1';
  case 2:  return '2';
  case 3:  return '3';
  case 4:  return '4';
  case 5:  return '5';
  case 6:  return '6';
  case 7:  return '7';
  case 8:  return '8';
  case 9:  return '9';
  case 10: return 'A';
  case 11: return 'B';
  case 12: return 'C';
  case 13: return 'D';
  case 14: return 'E';
  case 15: return 'F';
  }
  return '0';
}

string decToTwoHex(int num) {
  int z1, z2;
  z1 = num % 16;
  z2 = (num - z1) / 16;
  char c1, c2;
  c1 = decToHex(z1);
  c2 = decToHex(z2);
  return string()+c2+c1;
}

bool isDefined(string in) {
  for (int i = 0; i < d.size(); i++) {
    if (d[i].name == in) return true;
  }
  return false;
}

int main(int argc, char** argv) {
  // Check for correct number of arguments
  if (argc < 3) {
    cout<<"ERROR: please provide a input file name and a output file name!"<<endl;
    return 1;
  }

  string line;          // Single line from the input file
  vector<string> code;  // Vector containing every line from the input file
  int progLen = 0;      // Number of assembly instructions
  
  ifstream fi (argv[1]); // Getting the input file
 
  // Checking if the file opened correctly
  if (fi.is_open()) {
    
    // Adding lines from the file to the code vector and incrementing progLen
    while (getline(fi, line)) {
      if (!line.empty()) {
	while (line[0] == ' ' || line[0] == '\t') {    // Getting rid of spaces and tabs that are in front
	  line.erase(0, 1);
	}
      }
      if (line[0] == ';' || line[0] == '\n' || line.empty()) {    // Skipping empty lines and comments
	continue;
      }
      if (line[0] == '#') {    // Checking for compile time constants
	line.erase(0, 8);
	handleDefine(line);
	continue;
      }
      if (line[line.size() - 1] == ':') {    // Checking for labels
	line.erase(line.size() - 1, 1);
	handleLabel(line, progLen);
	continue;
      }
      
      // Adding the line to the code that needs to be assembled
      code.push_back(line);
      progLen++;
    }
    fi.close();
  }
  else {
    cout<<"ERROR: can't find file: "<<argv[1]<<endl;
    return 1;
  }
  // Create and open a text file
  ofstream fo(argv[2]);

  // Write to the file
  cout<<"DEBUG: len dec: "<<progLen<<endl;
  cout<<"DEBUG: len dec: "<<decToTwoHex(progLen)<<endl;
  fo<<decToTwoHex(progLen);
  
  // Assemble the code to its decimal representation
  for (int i = 0; i < progLen; i++) {
    vector<string> asmParts(4); // Vector for holding the instruction
    int part = 0; // What part of the asembly code we are reading

    for (int j = 0; j < code[i].size(); j++) { // Sort the parts of the instruction into asmParts
      if (code[i][j] != ' ') {
	asmParts[part] += code[i][j];
      } else {
	part++;
	if (part >= 4) {
	  cout<<"ERROR: incorrect syntax at line: "<<i<<endl;
	  return 1;
	}
      }
    }
    // fo<<"INST: "<<asmParts[0]<<" IN1: "<<asmParts[1]<<" IN2: "<<asmParts[2]<<" OUT: "<<asmParts[3]<<endl;
    int inst, in1, in2, out;

    // Assemble the instruction
    inst = assembleInstruction(asmParts[0]);
    in1 = assembleInput(asmParts[1]);
    in2 = assembleInput(asmParts[2]);
    out = assembleOutput(asmParts[3]);
    
    if (all_of(asmParts[1].begin(), asmParts[1].end(), ::isdigit) || isDefined(asmParts[1])) {
      inst += 128;
    }
    if (all_of(asmParts[2].begin(), asmParts[2].end(), ::isdigit) || isDefined(asmParts[2])) {
      inst += 64;
    }
    fo<<decToTwoHex(inst)<<decToTwoHex(in1)<<decToTwoHex(in2)<<decToTwoHex(out);
  }

  // Close the file
  fo.close();
}
