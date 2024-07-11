#include "Parse.h"

// Holds The Instructions
vector<int> instructs;
vector<int> lineNums;
TokenList* tl;


int line(){

  // Keeping Track of Line numbers
  int lineNum = 0;
  cout << "There are " << tl -> tokenList.size() << " Tokens" << endl;
  if(tl ->tokenList.front().tokenType == keyword::NUMBER) {
    lineNum =tl ->tokenList.front().number;
    lineNums.push_back(tl ->tokenList.front().tokenType);
    tl -> tokenList.pop_front();
  }

  // Loop Through Tokens Until CR is Found
  Token currentToken = tl ->tokenList.front();
  while(currentToken.tokenType != keyword::CR && !tl -> tokenList.empty()){

    tl -> tokenList.pop_front();
    currentToken = tl ->tokenList.front();

  }

  // TODO: If Line does not end with CR, ERROR

  if (tl ->tokenList.front().tokenType == keyword::CR){
    tl -> tokenList.pop_front();
  }else{
    cout << "ERROR: No Carriage Return After Line" << endl;
    exit(1);
  }

  // Print Line
  cout << "Line at " << lineNum << endl;

  return 0;
}

// Generates Instructrions
int generateCode(TokenList* tklist){

  tl = tklist;
  cout << "This is a Working Program" << endl;

  // Keep Generating Code Until No Token Left
  while(tl -> tokenList.empty() == false){

    line();

  }

  return 0;
};


// // // int statement(){}
// // // int var_list(){}
// // // int expr_list(){}
// // // int expression(){}
// // // int term(){}
// // // int var(){}
// // // int factor(){}
// // // int string(){}
// // // int relop(){}
// // // int syntax( TokenList tl ) {

// // //   // Take all the token

// // //   // Create Function for each variable in grammar

// // //   // If the function returns the file does not have errors

// // //   // Program can be run after this stage
// // // }
// // #include <string>
// // #include <iostream>

// // // This File handles Syntax and Code Generation of the DannyBASIC Compiler


// // // Numeric Variable Class
// // // class numStore{};

// class numVar{
// public:
//   int value;
//   int mark;
// };

// class numTable{
// public:
//   numVar vars[26];
//   void printTable();
//   numTable();
// };

// numTable::numTable(){
//   for(int i = 0; i < 26; i++ ){
//     // Set Mark to Zero
//     vars[i].mark = 0;

//   }
// }

// // void numTable::printTable(){

// //   for (int i = 0; i < 26; i++){
// //     if (numTable::vars[i].mark == 0){
// //       std::cout << "UNUSED" << std::endl;
// //     }else{
// //       std::cout << (char)('A' + i) << std::endl;
// //    }
// //   }
// // }



// // // String Variable Class

// // class stringVar{

// //   std::string s;
// //   int mark;
// // };

// // stringVar stringTable[26];

// // // class stringStore{};
