#ifndef PARSE_H
#define PARSE_H

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
  Token(keyword tT, int number, string name, string contents);
};
class TokenList{
public:
  std::list<Token> tokenList;
  void addToken(keyword type, int number, string name, string contents);
  void printAllTokens();
};

//Print the Source Code
void printSourceCode(std::ifstream* source);

// Print Error and Exits Program
void error(int num);

// Automata that Detects Tokens
int newline(ifstream* source);
int clear(ifstream* source);
int end(ifstream* source);
int chooseG(ifstream* sourece);
int chooseI(ifstream* source);
int chooseL(ifstream* source);
int print(ifstream* source);
int chooseR(ifstream* source);
int then(ifstream* source);
int String(ifstream* source);
int id(ifstream* source);
int number(ifstream* source);
int symbol(ifstream* source);
TokenList* startParse(ifstream* source);

#endif
