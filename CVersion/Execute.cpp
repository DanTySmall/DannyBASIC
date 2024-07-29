#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
int execute(){

  ifstream input;
  input.open("output.dyb");
  cout << "Im Executing" << endl;

  char c;
  // Parsing Instructions
  while (input.peek() != '\0'){
    input.get(c);
    cout << c;
  }
  return 1;
}
