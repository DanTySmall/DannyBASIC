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

void printStack(){

  cout << "===== Stack =====" << endl;
  for (int i = memory.size() - 1; i >= stackPtr; i--){
    cout << memory[i] << ' ';
  }

  cout << endl;
}

void printVars(){

  cout << "===== Variables =====" << endl;
  for (int i = varptr; i <= varptr + 25; i++){
    cout <<(char)('A' + i - varptr) << " : " << memory[i] << ' '<< endl;
  }

  cout << endl;
}

int run () {
  int program_counter = 0;
  int endOfProgram = 0;
  int ir[3];
  while(!endOfProgram){

    // Fetch
    ir[0] = memory[program_counter];
    ir[1] = memory[program_counter + 1];
    ir[2] = memory[program_counter + 2];

    cout << endl<< ir[0] << " " << ir[1] << " " << ir[2] << endl;

    // Execute
    switch (ir[0]) {
    case 1: // Literal
      stackPtr = stackPtr - 1;
      memory[stackPtr] = ir[2];
      break;

    case 2: // Math Operations / Return
      switch (ir[2]) {
      case 1:
        memory[stackPtr + 1] = memory[stackPtr + 1] + memory[stackPtr];
        stackPtr = stackPtr + 1;
        break;

      case 2:
        memory[stackPtr + 1] = memory[stackPtr + 1] - memory[stackPtr];
        stackPtr = stackPtr + 1;
        break;

      case 3:
        memory[stackPtr + 1] = memory[stackPtr + 1] * memory[stackPtr];
        stackPtr = stackPtr + 1;
        break;

      case 4:
        memory[stackPtr + 1] = memory[stackPtr + 1] / memory[stackPtr];
        stackPtr = stackPtr + 1;
        break;

      case 5:
        memory[stackPtr + 1] = memory[stackPtr + 1] == memory[stackPtr];
        stackPtr = stackPtr + 1;
        break;

      case 6:
        memory[stackPtr + 1] = memory[stackPtr + 1] != memory[stackPtr];
        stackPtr = stackPtr + 1;
        break;

      case 7:
        memory[stackPtr + 1] = memory[stackPtr + 1] < memory[stackPtr];
        stackPtr = stackPtr + 1;
        break;

      case 8:
        memory[stackPtr + 1] = memory[stackPtr + 1] <= memory[stackPtr];
        stackPtr = stackPtr + 1;
        break;

      case 9:
        memory[stackPtr + 1] = memory[stackPtr + 1] >  memory[stackPtr];
        stackPtr = stackPtr + 1;
        break;
      case 10:
        memory[stackPtr + 1] = memory[stackPtr + 1] >= memory[stackPtr];
        stackPtr = stackPtr + 1;
        break;
      }
      break;

    case 3:
       stackPtr = stackPtr - 1;
       memory[stackPtr] = memory[varptr + ir[2]];
       break;

    case 4:
      memory[varptr + ir[2]] = memory[stackPtr];
      stackPtr = stackPtr + 1;

    }

    printStack();
    program_counter += 3;
    if(program_counter >= strptr) endOfProgram = 1;

  }

  printVars();
  return 1;
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

  run();



  return 1;
}
