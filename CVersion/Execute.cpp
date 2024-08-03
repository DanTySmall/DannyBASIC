#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
vector<int> memory;
int strptr;
int varptr;
int stackPtr;

class LineAddress {
public:
  int lineNum;
  int instructPtr;
  LineAddress(int lineNum, int instructPtr){
    this->lineNum = lineNum;
    this->instructPtr = instructPtr;
  }

};
vector<LineAddress> lines;

void printMemory(){

  cout << "===== MEMORY CONTENTS =====" << endl;

  int size = memory.size();
  for(int i = 0; i < size; i++){
    if (i == strptr){
      cout << "-- Strings --" << endl;
    } else if (i == varptr){
      cout << "-- Vars --" << endl;
    } else if (i == stackPtr){
      cout << "-- Stack --" << endl;
    }
    cout << memory[i] << endl;

  }


}

int execute(){

  ifstream input;
  input.open("output.dyb");
  cout << "Im Executing" << endl;

  char c;
  int n;

  int instruction;

  // Parsing Instructions
  while (input >> instruction){
    memory.push_back(instruction);
    input >> c;
    if(c == '\0') {
      cout<< "break" << endl;
      break;
    }else{
      input.putback(c);
    }
    cout << instruction<< endl;
  }

  strptr = memory.size();
  vector<char> strings;

  // Parsing Strings
  while (input.get(c)){
    input.get(c);
    cout << c;
    memory.push_back(c);
    if(c == '\0') {
      input >> c;
      cout<< c;
      if(c == '\0'){
        break;
      }else{
        input.putback(c);
      }

    }else{
      input.putback(c);
    }

  }

  varptr = memory.size();

  // Adding Vars and Stack Space
  memory.resize(memory.size() + 526 , 0);
  stackPtr = memory.size();

  // Parsing Line Address
  cout << endl;
  int m;
  while (input >> n) {
    input >> m;
    lines.push_back(LineAddress(n,m));
    input.get(c);
  }

  for (LineAddress l : lines){

    cout << l.lineNum << " , " <<  l.instructPtr << endl;
  }

  // printMemory();

  return 1;
}
