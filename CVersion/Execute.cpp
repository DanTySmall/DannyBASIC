#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
int execute(){

  ifstream input;
  input.open("output.dyb");
  cout << "Im Executing" << endl;

  char c;
  int n;

  vector<int> memory;
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

  vector<char> strings;

  // Parsing Strings
  while (input.get(c)){
    input.get(c);
    cout << c;
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

  // Parsing Line Address
  cout << endl;
  while (input >> n) {
    cout << n << endl;
    input.get(c);
  }


  cout <<  (input.good()) << endl;

  return 1;
}
