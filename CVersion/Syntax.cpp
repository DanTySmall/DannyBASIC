#include "Parse.h"

// Holds The Instructions
vector<int> instructs;
vector<int> lineNums;
TokenList* tl;


int genStatement(){

  Token currentToken = tl -> tokenList.front();
 switch (currentToken.tokenType) {

 case keyword::PRINT: {cout << "This is a PRINT Statement" << endl; break;}
 case keyword::IF: {cout << "This is a IF Statement" << endl; break;}
 case keyword::GOTO: {cout << "This is a GOTO Statement" << endl; break;}
 case keyword::INPUT: {cout << "This is a INPUT Statement" << endl; break;}
 case keyword::LET: {cout << "This is a LET Statement" << endl; break;}
 case keyword::GOSUB: {cout << "This is a GOSUB Statement" << endl; break;}
 case keyword::RETURN: {cout << "This is a RETURN Statement" << endl; break;}
 case keyword::CLEAR: {cout << "This is a CLEAR Statement" << endl; break;}
 case keyword::LIST: {cout << "This is a LIST Statement" << endl; break;}
 case keyword::RUN: {cout << "This is a RUN Statement" << endl; break;}
 case keyword::END: {cout << "This is a END Statement" << endl; break;}
 default: {cout << "ERROR: String cant be parsed"; exit(1);}

 }




  return 1;

}
int line(){

  // Keeping Track of Line numbers
  int lineNum = 0;
  // cout << "There are " << tl -> tokenList.size() << " Tokens" << endl;
  if(tl ->tokenList.front().tokenType == keyword::NUMBER) {
    lineNum =tl ->tokenList.front().number;
    lineNums.push_back(tl ->tokenList.front().tokenType);
    tl -> tokenList.pop_front();
  }

  // Print Line
  cout << "Line at " << lineNum << endl;

  genStatement();



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


  return 0;
}

// Generates Instructrions
int generateCode(TokenList* tklist){

  tl = tklist;
  cout << "===== Code Generation =====" << endl;

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
