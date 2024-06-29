// // #include "Parse.cpp"

// // // int line(){

// //     // Number (Optional)
// //     // Statement
// //     // CR

// // // }

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
