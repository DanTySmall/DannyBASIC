#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <cstring>
#include <string>
#include <vector>
#include "Parse.cpp"
#include "Syntax.cpp"
using namespace std;

int main(int argc, char *argv[]) {

  // Creating and Opening File Object
  ifstream source("test.bsc");

  // File Does Not Exist
  if(!source.good()){
    cout << "Program Does Not Exist or Missing File"<< endl;
  }

  // Print the Original Source Code
  printSourceCode(&source);
  source.close();

  // Reset file pointer and start parsing
  source.open("test.bsc");

  // Parses Source File
  startParse(&source);

  // DEBUG: Prints All Tokens
  tl.printAllTokens();

  // Closes File and Exits Program
  source.close();
  return 0;
}
