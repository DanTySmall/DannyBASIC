#include <iostream>
#include <fstream>
#include "Parse.h"
#include "Syntax.hpp"
#include "Execute.hpp"
using namespace std;

int main(int argc, char *argv[]) {

  // Creating and Opening File Object
  string filePath;
  ifstream source;
  if(argc < 2) {
    cout << "Enter File Path: ";
    getline(cin, filePath);
    source = ifstream(filePath);

    while (source.is_open() == 0){
      cout << "Oops! File Not Not Found. Try Again: ";
      getline(cin, filePath);
      source.open(filePath);
    }

  }else{

    cout << "File: " << argv[1] << endl;
    source = ifstream(argv[1]);

  }

  // File Does Not Exist
  if(!source.good()){
    cout << "Program Does Not Exist or Missing File"<< endl;
  }

  // Print the Original Source Code
  printSourceCode(&source);
  source.close();

  // Reset file pointer and start parsing
  if(argc < 2) {

    source.open(filePath);
  } else {

    source.open(argv[1]);
  }

  // Parses Source File
  TokenList* tl = startParse(&source);

  // Closes File and Exits Program
  source.close();

  // Generates Code From Tokens
  generateCode(tl);

  // Print The Generated Code
  printCode();

  // Execute Program
  execute();
  return 0;
}
