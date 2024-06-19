#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <cstring>
#include <string>
#include <vector>
using namespace std;
// This is the Parser for DannyBasic: A compiler for TinyBasic made by Daniel Small
enum keyword {
  ID,
  NUMBER,
  CR,
  CLEAR,
  END,
  GOTO,
  GOSUB,
  INPUT,
  IF,
  LET,
  LIST,
  PRINT,
  RETURN,
  RUN,
  THEN,
  LSS,
  LEQ,
  NEQ,
  NNEQ,
  GEQ,
  GTR,
  ADD,
  SUB,
  DIV,
  MOD,
  MULT,
  STRING,
  EQL,
  EQUALITY
};

class Token {
public:
  keyword tokenType;
  int number;
  string name;
  string contents;

  Token(keyword tT, int number, string name, string contents){
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
  std::string keywords[29] = {"Identifier", "Number", "CR", "CLEAR", "END", "GOTO", "GOSUB",
    "INPUT", "IF", "LET", "LIST", "PRINT", "RETURN", "RUN", "THEN", "<", "<=", "<>", "><", ">=",
">" ,"+" ,"_" ,"/" ,"%", "*", "STRING","=","=="};
  void addToken(keyword type, int number, string name, string contents){

    tokenList.push_back(Token(type,number,name,contents));

  }

  // TODO: Print More than just tokenType
  void printAllTokens(){

    for (Token token: tokenList ){
      if(token.tokenType == STRING){
        cout << keywords[token.tokenType] << "\t" << token.contents << endl;
      }else if(token.tokenType == NUMBER){
        cout << keywords[token.tokenType] << "\t" << token.number << endl;
      }else if(token.tokenType == ID){
        cout << keywords[token.tokenType] << "\t" << token.name << endl;
      }else
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
int newline(ifstream* source){

  // NULL CHECK
  if (!source -> good()) return !source -> good();

  // Check for carriage return CR
  char c;
  source->get(c);
  if (c == '\n')
    tl.addToken(keyword::CR,0,"","");
  else{
    source->putback(c);
    error(2);
  }

  return source->good();
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

      // Make sure this is the right token number, it might have change from when this was eritten
      tl.addToken(CLEAR, 0, "", "");
      break;

    }

    source->get(c);

  }

  return source->good();
}
int end(ifstream* source){

  // NULL CHECK
  if (!source -> good()) return !source -> good();

  // Keyword and Buffer
  char keyword[] = "END";
  char buffer[3];
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
      tl.addToken(END, 0, "", "");
      break;

    }

    source->get(c);

  }

  return source->good();
}
int chooseG(ifstream* source){

  // NULL CHECK
  if (!source -> good()) return !source -> good();

  // Keyword and Buffer
  string keyword = "GOTO";
  char* buffer = new char[keyword.length()];
  char c;
  int length = keyword.length();

  // Check for each letter of keyword
  source->get(c);
  for (int i = 0; i < length; i++){

    // If you reach end, treat what is in buffer as an identifier
    // if (source->eof()) {fp = identifier(fp); return fp;}

    // Check if char is in keyword
    if(c == keyword[i]) { // if match put char in buffer
      buffer[i] = keyword[i];
    }else{ // if it doesnt match, put everything back and call identifier
      source->putback(c);
      for(int j = i-1; j  >= 0; j--){
        source->putback(buffer[j]);
      }
      // fp = identifier(fp);
      break;
    }

    // Keyword was found, add token to list
    if(i == length-1){

      // Make sure this is the right token number, it might have change from when this was written
      tl.addToken(GOTO, 0, "", "");
      source->putback(c);
      return source->good();

    }

    source->get(c);

  }

  delete(buffer);
  keyword = "GOSUB";
  length = keyword.length();
  buffer = new char[length];
  source->get(c);
  for (int i = 0; i < length; i++){

    // If you reach end, treat what is in buffer as an identifier
    // if (source->eof()) {fp = identifier(fp); return fp;}

    // Check if char is in keyword
    if(c == keyword[i]) { // if match put char in buffer
      buffer[i] = keyword[i];
    }else{ // if it doesnt match, put everything back and call identifier
      for(int j = i; j  >= 0; j--)source->putback(buffer[j]);
      // fp = identifier(fp);
      break;
    }

    // Keyword was found, add token to list
    if(i == length-1){

      // Make sure this is the right token number, it might have change from when this was written
      tl.addToken(GOSUB, 0, "", "");
      break;

    }

    source->get(c);

  }

  source->putback(c);
  return source->good();
}
int chooseI(ifstream* source){

  // NULL CHECK
  if (!source -> good()) return !source -> good();

  // Keyword and Buffer
  string keyword = "IF";
  char c;
  int length = keyword.length();
  char* buffer = new char[length];

  // Check for each letter of keyword
  source->get(c);
  for (int i = 0; i < length; i++){

    // If you reach end, treat what is in buffer as an identifier
    // if (source->eof()) {fp = identifier(fp); return fp;}

    // Check if char is in keyword
    if(c == keyword[i]) { // if match put char in buffer
      buffer[i] = keyword[i];
    }else{ // if it doesnt match, put everything back and call identifier
      source->putback(c);
      for(int j = i-1; j  >= 0; j--){
        source->putback(buffer[j]);
      }
      // fp = identifier(fp);
      break;
    }

    // Keyword was found, add token to list
    if(i == length-1){

      // Make sure this is the right token number, it might have change from when this was written
      tl.addToken(IF, 0, "", "");
      source->putback(c);
      return source->good();

    }

    source->get(c);

  }

  delete(buffer);
  keyword = "INPUT";
  length = keyword.length();
  buffer = new char[length];
  source->get(c);
  for (int i = 0; i < length; i++){

    // If you reach end, treat what is in buffer as an identifier
    // if (source->eof()) {fp = identifier(fp); return fp;}

    // Check if char is in keyword
    if(c == keyword[i]) { // if match put char in buffer
      buffer[i] = keyword[i];
    }else{ // if it doesnt match, put everything back and call identifier
      for(int j = i; j  >= 0; j--)source->putback(buffer[j]);
      // fp = identifier(fp);
      break;
    }

    // Keyword was found, add token to list
    if(i == length-1){

      // Make sure this is the right token number, it might have change from when this was written
      tl.addToken(INPUT, 0, "", "");
      break;

    }

    source->get(c);

  }

  delete(buffer);
  return source->good();
}
int chooseL(ifstream* source){

  // NULL CHECK
  if (!source -> good()) return !source -> good();

  // Keyword and Buffer
  string keyword = "LET";
  char c;
  int length = keyword.length();
  char* buffer = new char[length];

  // Check for each letter of keyword
  source->get(c);
  for (int i = 0; i < length; i++){

    // If you reach end, treat what is in buffer as an identifier
    // if (source->eof()) {fp = identifier(fp); return fp;}

    // Check if char is in keyword
    if(c == keyword[i]) { // if match put char in buffer
      buffer[i] = keyword[i];
    }else{ // if it doesnt match, put everything back and call identifier
      source->putback(c);
      for(int j = i-1; j  >= 0; j--){
        source->putback(buffer[j]);
      }
      // fp = identifier(fp);
      break;
    }

    // Keyword was found, add token to list
    if(i == length-1){

      // Make sure this is the right token number, it might have change from when this was written
      tl.addToken(LET, 0, "", "");
      // source->putback(c);
      return source->good();

    }

    source->get(c);

  }

  delete(buffer);
  keyword = "LIST";
  length = keyword.length();
  buffer = new char[length];
  source->get(c);
  for (int i = 0; i < length; i++){

    // If you reach end, treat what is in buffer as an identifier
    // if (source->eof()) {fp = identifier(fp); return fp;}

    // Check if char is in keyword
    if(c == keyword[i]) { // if match put char in buffer
      buffer[i] = keyword[i];
    }else{ // if it doesnt match, put everything back and call identifier
      for(int j = i; j  >= 0; j--)source->putback(buffer[j]);
      // fp = identifier(fp);
      break;
    }

    // Keyword was found, add token to list
    if(i == length-1){

      // Make sure this is the right token number, it might have change from when this was written
      tl.addToken(LIST, 0, "", "");
      break;

    }

    source->get(c);

  }

  delete(buffer);
  // source->putback(c);
  return source->good();
}
int print(ifstream* source){

  // NULL CHECK
  if (!source -> good()) return !source -> good();

  // Keyword and Buffer
  char keyword[] = "PRINT";
  char buffer[3];
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
      tl.addToken(PRINT, 0, "", "");
      break;

    }

    source->get(c);

  }

  // source->putback(c);
  return source->good();
}
int chooseR(ifstream* source){

  // NULL CHECK
  if (!source -> good()) return !source -> good();

  // Keyword and Buffer
  string keyword = "RETURN";
  char c;
  int length = keyword.length();
  char* buffer = new char[length];

  // Check for each letter of keyword
  source->get(c);
  for (int i = 0; i < length; i++){

    // If you reach end, treat what is in buffer as an identifier
    // if (source->eof()) {fp = identifier(fp); return fp;}

    // Check if char is in keyword
    if(c == keyword[i]) { // if match put char in buffer
      buffer[i] = keyword[i];
    }else{ // if it doesnt match, put everything back and call identifier
      source->putback(c);
      for(int j = i-1; j  >= 0; j--){
        source->putback(buffer[j]);
      }
      // fp = identifier(fp);
      break;
    }

    // Keyword was found, add token to list
    if(i == length-1){

      // Make sure this is the right token number, it might have change from when this was written
      tl.addToken(RETURN, 0, "", "");
      source->putback(c);
      return source->good();

    }

    source->get(c);

  }

  delete(buffer);
  keyword = "RUN";
  length = keyword.length();
  buffer = new char[length];
  source->get(c);
  for (int i = 0; i < length; i++){

    // If you reach end, treat what is in buffer as an identifier
    // if (source->eof()) {fp = identifier(fp); return fp;}

    // Check if char is in keyword
    if(c == keyword[i]) { // if match put char in buffer
      buffer[i] = keyword[i];
    }else{ // if it doesnt match, put everything back and call identifier
      for(int j = i; j  >= 0; j--)source->putback(buffer[j]);
      // fp = identifier(fp);
      break;
    }

    // Keyword was found, add token to list
    if(i == length-1){

      // Make sure this is the right token number, it might have change from when this was written
      tl.addToken(RUN, 0, "", "");
      break;

    }

    source->get(c);

  }

  delete(buffer);
  source->putback(c);
  return source->good();
}
int then(ifstream* source){

  // NULL CHECK
  if (!source -> good()) return !source -> good();

  // Keyword and Buffer
  char keyword[] = "THEN";
  char buffer[3];
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
      tl.addToken(THEN, 0, "", "");
      break;

    }

    source->get(c);

  }

  // source->putback(c);
  return source->good();
}
int String(ifstream* source){

  // NULL CHECK
  if (!source -> good()) return !source -> good();

  // Check for Open Quotes
  char c;
  source->get(c);
  if (c != '"') error(3);
  source->get(c);

  // Obtain String Contents
  vector<char> contents = {};
  while(c != '"'){

    // Add Char to Vector
    contents.push_back(c);

    // Get Char
    source->get(c);

    // Your going to need to check if the program has reached end of file

  }

  // Remove Closing Quotes
  source->get(c);

  // Add String to TokenList
  string content(contents.begin(),contents.end());
  tl.addToken(keyword::STRING,0,"",content);

  return source->good();
}
int id(ifstream* source){

  // NULL CHECK
  if (!source -> good()) return !source -> good();

  // Check for English Letter
  char c;
  source->get(c);
  if (c >= 'A' && c <= 'Z')
    tl.addToken(keyword::ID,0,string(&c),"");
  else{
    source->putback(c);
    error(2);
  }

  return source->good();
}

int number(ifstream* source){

  // NULL CHECK
  if (!source -> good()) return !source -> good();

  // Receive number and check if too big
  int limit = (1<< 15);
  int current = 0;
  char c;
  source->get(c);
  if(!(c >= '0' && c <= '9')) error(4);
  while(c >= '0' && c <= '9'){

    if(current > limit) error(5);
    current *= 10;
    current += c - '0';
    source->get(c);

  }
  source->putback(c);

  // Add to TokenList
  tl.addToken(keyword::NUMBER,current,"","");

  return source->good();
}


int symbol(ifstream* source){

  // NULL CHECK
  if (!source -> good()) return !source -> good();

  // Check for carriage return CR
  char c;
  source->get(c);
  switch (c) {

  case '<': {
    source->get(c);
    if(c == '=')tl.addToken(keyword::LEQ,0,"",""); // Less than or Equal to
    else if(c == '>')tl.addToken(keyword::NEQ,0,"",""); // Not Equal
    else{source->putback(c); tl.addToken(keyword::LSS,0,"","");}// Less than
    break;
  }

  case '>': {
    source->get(c);
    if(c == '=')tl.addToken(keyword::GEQ,0,"","");// Greater than or Equal to
    else if(c == '<')tl.addToken(keyword::NEQ,0,"","");// Not Equal
    else{source->putback(c); tl.addToken(keyword::GTR,0,"","");}// Greater Than
    break;
  }

  case '+': {tl.addToken(keyword::ADD,0,"",""); break;}// Addition
  case '-': {tl.addToken(keyword::SUB,0,"",""); break;}// Subtraction
  case '/': {tl.addToken(keyword::DIV,0,"",""); break;}// Division
  case '%': {tl.addToken(keyword::MOD,0,"",""); break;}// Modulus
  case '*': {tl.addToken(keyword::MULT,0,"",""); break;}// Multiplication
  case '=': {
    source->get(c);
    if(c == '=')tl.addToken(keyword::EQUALITY,0,"",""); // Equality
    else{source->putback(c); tl.addToken(keyword::EQL,0,"","");}// Assignment
    break;
  }

  default: error(6);
  }


  return source->good();
}

int startParse(ifstream* source){

  // NULL CHECK
  if (!source -> good()) return !source -> good();

  char c;
  while (source->get(c)) {
    if(c == ' ' || c == '\t') {source->get(c); continue;}
    switch (c) {

    case '\n': {source->putback('\n'); newline(source); break;}
    case 'C': {source->putback('C'); clear(source); break;}
    case 'E': {source->putback('E'); end(source); break;}
    case 'G': {source->putback('G'); chooseG(source); break;}
    case 'I': {source->putback('I'); chooseI(source); break;}
    case 'L': {source->putback('L'); chooseL(source); break;}
    case 'P': {source->putback('P'); print(source); break;}
    case 'R': {source->putback('R'); chooseR(source); break;}
    case 'T': {source->putback('T'); then(source); break;}
    case '"': {source->putback('"'); String(source); break;}
    default:
      if(c >= 'A' && c <= 'Z') {source->putback(c); id(source); break;}
      if(c >= '0' && c <= '9') {source->putback(c); number(source); break;}
    //   Non-Alphanumeric Symbols and invalid symbols
      source->putback(c);
      symbol(source);
    //

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

  tl.printAllTokens();

  source.close();
  return 0;
}
