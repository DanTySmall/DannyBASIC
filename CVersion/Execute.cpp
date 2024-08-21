#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
vector<int> memory;
vector<int> strings;
int strptr;
int varptr;
int stackPtr;
int basePtr = 0;


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

  cout << endl << "===== Stack =====" << endl;
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

  // cout << endl;
}

int findLinePtr(int line){

  for(LineAddress l : lines){
    if (l.lineNum == line){
      return l.instructPtr;
      break;
    }
  }

  // If this is reach the Line Number does not exist
  cout << "ERROR: Line " << memory[stackPtr] << " does not exit" << endl;
  exit(1);

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
    program_counter += 3;

    // cout << endl<< ir[0] << " " << ir[1] << " " << ir[2] << endl;

    // Execute
    switch (ir[0]) {
    case 1: // Literal
      stackPtr = stackPtr - 1;
      memory[stackPtr] = ir[2];
      break;

    case 2: // Math Operations / Return
      switch (ir[2]) {

      case 0: // RTN
        stackPtr = basePtr + 1;
        program_counter = memory[basePtr - 1];
        basePtr = memory[stackPtr];
        break;

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
      break;

    case 5:
      memory[stackPtr - 1] = basePtr;
      memory[stackPtr - 2] = program_counter;
      basePtr = stackPtr - 1;
      program_counter = findLinePtr(ir[2]);
      stackPtr = stackPtr - 2;
      break;

    // case 6: INC not needed, no local variable

    case 7:
      if(ir[1] != 1){
        cout << "I don't know how you got here." << endl;
        exit(1);
      }

      program_counter = findLinePtr(memory[stackPtr]);
      stackPtr = stackPtr - 1;
      break;

    case 8:
      if (memory[stackPtr] == 0){
        program_counter = ir[2];
      }
      stackPtr = stackPtr + 1;
      break;

    case 9:

      if(ir[1] == 1){ // Printing

        if(ir[2] == -1) {
          cout << '\n';
          break;
        }

        for (int position = strings[ir[2]];
             position < memory.size() && memory[position] != '\0';
             position++){
          cout << (char) memory[position];
        }
        cout << ' ';
        break;

      }
      switch(ir[2]){
      case 1:
        cout << memory[stackPtr] << ' ';
        stackPtr = stackPtr + 1;
        break;

      case 2:
        stackPtr = stackPtr - 1;
        int x;
        cin >> x;
        memory[stackPtr] = x;
        break;

      case 3:
        cout << "Program Ended Successfully";
        exit(0);
        break;
      }

    }

    // printStack();
    // printMemory();
    if(program_counter >= strptr) endOfProgram = 1;

  }

  // printVars();
  return 1;
}

int execute(){

  ifstream input;
  input.open("output.dyb");
  // cout << "Im Executing" << endl;

  char c;
  int n;

  int instruction;

  // Parsing Instructions
  while (input >> instruction){
    memory.push_back(instruction);
    input >> c;
    if(c == '\0') {
      // cout<< "break" << endl;
      break;
    }else{
      input.putback(c);
    }
    // cout << instruction<< endl;
  }

   input.putback(c);

  strptr = memory.size();
  // vector<char> strings;

  // Parsing Strings
  strings.push_back(strptr);
  input.get(c);
  while(c == '\0' || c == '\n'){
   input.get(c);
  }
  input.putback(c);
  // cout << "String at 0" << endl;
  int position = 1;
  while (input.get(c)){

    // input.get(c);
    // cout << c;
    memory.push_back(c);
    if(c == '\0') { // End

      input >> c;

      if(c == '\0'){ // End of All Strings
        // strings.pop_back();
        break;
      }else{ // End of Single String
        strings.push_back(strptr + position  );
        // cout << "String at " << position << endl;
        // memory.push_back(c);
        input.putback(c);
      }

    }

    position++;
  }


  // cout << endl << "===== Strings Collected =====" << endl;

  // for(int i = 0; i < strings.size(); i++){

  //   for (int j = strings[i];
  //        memory[j] != '\0';
  //        j++){
  //     cout << (char)memory[j];
  //   }
  //   cout << endl;

  // }

  // cout << "===== String Memory =====" << endl;

  // for(int i = strptr; i < memory.size(); i++){
  //   cout << (char)memory[i];
  // }



  varptr = memory.size();

  // Adding Vars and Stack Space
  memory.resize(memory.size() + 526 , 0);
  stackPtr = memory.size();

  // Parsing Line Address
  // cout << endl;
  int m;
  while (input >> n) {
    input >> m;
    lines.push_back(LineAddress(n,m));
    input.get(c);
  }

  // for (LineAddress l : lines){

  //   cout << l.lineNum << " , " <<  l.instructPtr << endl;
  // }


  run();



  return 1;
}
