#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <cstring>
#include <string>
using namespace std;
// This is the Parser for DannyBasic: A compiler for TinyBasic made by Daniel Sll

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

// UNTESTED
class TokenList{
public:
  std::list<Token> tokenList;
  std::string keywords[27] = {"Identifier", "Number", "CR", "CLEAR", "END", "GOTO", "GOSUB",
    "INPUT", "IF", "LET", "LIST", "PRINT", "RETURN", "RUN", "THEN", "<", "<=", "<>", "><", ">=",
">" ,"+" ,"_" ,"/" ,"%", "*", "string"};
  void addToken(int type, int number, string name, string contents){

    tokenList.push_back(Token(type,number,name,contents));

  }

  // TODO: Print More than just tokenType
  void printAllTokens(){

    for (Token token: tokenList ){
     cout << keywords[token.tokenType] << endl;
    }

  }
};

// TokenList that holds all tokens
TokenList tl = TokenList();

// Print the Source Code
void printSourceCode(ifstream* source){
  if(!source->good()) return;

  cout << "Source Code: \n";
  char c;
  while (source->get(c)) {
    printf("%c", c);
  }

  printf("\n\n");
}

void error(int num){


  exit(num);
}

FILE* newline(FILE* fp);
FILE* identifier(FILE* fp);
// Automata that Detects Tokens
FILE* newline(FILE* fp){

  // NULL CHECK
  if (!fp) return fp;

  // Check for carriage return CR
  if (char c = fgetc(fp) == '\n')
    tl.addToken(3,0,NULL,NULL);
  else{
    fputc(c,fp);
    error(2);
  }


  return fp;
}
int clear(ifstream* source){

  // NULL CHECK
  if (!source -> good()) return !source -> good();

  // Keyword and Buffer
  char keyword[] = "CLEAR";
  char buffer[5];
  char c;
  int length = strlen(keyword);

  // Check for each letter of keyword
  source->get(c);
  for (int i = 0; i < length; i++){

    // If you reach end, treat what is in buffer as an identifier
    // if (source->eof()) {fp = identifier(fp); return fp;}

    // Check if char is in keyword
    if(c == keyword[i]) { // if match put char in buffer
      buffer[i] = keyword[i];
    }else{ // if it doesnt match, put everything back and call identifier
      for(int j = i; j  >= 0; j--)source->putback(buffer[i]);
      // fp = identifier(fp);
      break;
    }

    // Keyword was found, add token to list
    if(i == length-1){
      // Make sure this is the right token number, it might have change from when this was written
      tl.addToken(4, 0, "", "");
      printf("Found!\n");
    }

    source->get(c);

  }

  return source->good();
}

// FILE* end(FILE* fp){}
// FILE* chooseG(FILE* fp){}
// FILE* chooseI(FILE* fp){}
// FILE* chooseL(FILE* fp){}
// FILE* print(FILE* fp){}
// FILE* chooseR(FILE* fp){}
// FILE* then(FILE* fp){}
// FILE* identifier(FILE* fp){}
// FILE* number(FILE* fp){}
// FILE* symbol(FILE* fp){}
// FILE* astring(FILE* fp){}
int startParse(ifstream* source){

  // NULL CHECK
  if (!source -> good()) return !source -> good();

  char c;
  while (source->get(c)) {
    if(c == ' ' || c == '\t') {source->get(c); continue;}
    switch (c) {

    case '\n': {source->putback('\n'); clear(source); cout << "CR DETECTED"; break;}
    case 'C': {source->putback('C'); source -> get(c); break;}
    // case 'E': {fputc('E', fp); end(fp); break;}
    // case 'G': {fputc('G', fp); chooseG(fp); break;}
    // case 'I': {fputc('I', fp); chooseI(fp); break;}
    // case 'L': {fputc('L', fp); chooseL(fp); break;}
    // case 'P': {fputc('P', fp); print(fp); break;}
    // case 'R': {fputc('R', fp); chooseR(fp); break;}
    // case 'T': {fputc('T', fp); then(fp); break;}
    // case '"': fputc('"', fp); newline(fp); break;
    // default:
    //   if(c >= 'A' && c <= 'Z') fp = identifier(fp);
    //   if(c >= '0' && c <= '9') fp = number(fp);
    //   fp = symbol(fp);
    }

  }

  return 0;
}

int main(int argc, char *argv[]) {


  // File IO
  // No File Mentioned
  // if (argc < 2){

  //   cout << "No File was Provided" << endl;
  //   exit(1);

  // }

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
  // For Debugging  fp = fopen(argv[1], "r");
  // fp = fopen("test.bsc", "r");

  startParse(&source);

  // tl.printAllTokens();

  source.close();
  return 0;
}
