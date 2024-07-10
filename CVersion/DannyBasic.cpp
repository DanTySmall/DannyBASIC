#include <iostream>
#include <fstream>
#include "Parse.h"
#include "Syntax.hpp"
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
  TokenList* tl = startParse(&source);

  // DEBUG: Prints All Tokens
  tl->printAllTokens();

  // Closes File and Exits Program
  source.close();

  // Generates Code From Tokens
  generateCode(tl);

  return 0;
}
