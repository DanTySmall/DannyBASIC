#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <list>
using namespace std;
// This is the Parser for DannyBasic: A compiler for TinyBasic made by Daniel Small
//

class Token {
public:
  int tokenType;
  int number;
  string name;
  string contents;

  Token(int tT, int number, string name, string contents){
    this-> tokenType = tT;
    this-> number = number;
    this-> name = name;
    this-> contents = contents;
  }
};
/*
node *aNode = new node(14, 32);
std::list<node*> dataSet;
dataSet.insert(dataSet.begin(), aNode);
*/

// UNTESTED
class TokenList{
public:
  std::list<Token> tokenList;

  void addToken(int type, int number, string name, string contents){

    tokenList.push_back(new Token(type,number,name,contents));

  }

  // TODO: Print More than just tokenType
  void printAllToken(){

    for (Token token: tokenList ){
     cout << token.tokenType << endl;
    }

  }
};

// Print the Source Code
void printSourceCode(FILE* fp){
  if(!fp) return;

  cout << "Source Code: \n";
  char c = getc(fp);
  while (c != EOF) {

    printf("%c", c);
    c = getc(fp);
  }

  printf("\n\n");


}


FILE* newline(FILE* fp);
// Automata that Detects Tokens
FILE* newline(FILE* fp){

  // NULL CHECK
  if (!fp) return fp;


}
FILE* clear(FILE* fp){}
FILE* end(FILE* fp){}
FILE* chooseG(FILE* fp){}
FILE* chooseI(FILE* fp){}
FILE* chooseL(FILE* fp){}
FILE* print(FILE* fp){}
FILE* chooseR(FILE* fp){}
FILE* then(FILE* fp){}
FILE* identifier(FILE* fp){}
FILE* number(FILE* fp){}
FILE* relop(FILE* fp){}
FILE* astring(FILE* fp){}
FILE* startParse(FILE* fp){

  // NULL CHECK
  if (!fp) return fp;

  char c = fgetc(fp);
  while (!feof(fp)){
    switch (c) {

    case '\n': fputc('\n', fp); newline(fp); break;
    }

  }





}

int main(int argc, char *argv[]) {


  // File IO
  FILE* fp;

  // No File Mentioned
  if (argc < 2){

    printf("No File was Provided");
    exit(1);

  }

  // Open File
  fp = fopen(argv[1], "r");

  // Print the Original Source Code
  printSourceCode(fp);

  // Reset file pointer and start parsing
  fp = fopen(argv[1], "r");




  return 0;
}
