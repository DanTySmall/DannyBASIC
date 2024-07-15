#include "Parse.h"

// Holds The Instructions
vector<int> instructs;
TokenList* tl;
int stringCount = 0;
vector<string> stringData;

class LineAddress {
public:
  int lineNum;
  int instructPtr;
  LineAddress(int lineNum, int instructPtr){
    this->lineNum = lineNum;
    this->instructPtr = instructPtr;
  }

};

// LATER: This Could Be a Tree
vector<LineAddress> lineNums;

void addLine (int lineNum){

  // Search Vector for the Smallest Line Number Greater than Line Number
  int size = lineNums.size();
  bool added = false;
  for(int i = 0; i < size; i++){

    // Place New Line Address before
    if(lineNums[i].lineNum > lineNum){
      added = true;
      lineNums.insert(lineNums.begin()+ i, LineAddress(lineNum, instructs.size()));
      break;
    }
  }

  if(!added) lineNums.emplace_back(LineAddress(lineNum, instructs.size()));

}

int addressAtLine(int lineNum){

  // Search Vector for the Smallest Line Number Greater than Line Number

  int size = lineNums.size();
  bool found = false;
  for(int i = 0; i < size; i++){

    // Place New Line Address before
    if(lineNums[i].lineNum == lineNum){
      found = true;
      return lineNums[i].instructPtr;
    }
  }

  if(!found) {
    cout << "Error: Undefined Line Number" << endl;
    exit(1);
  }
return instructs.size();
}



int expression();

int genStatement();

void emit(int op, int l, int m){

  instructs.push_back(op);
  instructs.push_back(l);
  instructs.push_back(m);


}

int factor(){

  Token currentToken = tl -> tokenList.front();
  if (currentToken.tokenType == keyword::ID){

    cout << "LOD 0 " << (int)(currentToken.name.at(0) - 'A') << endl;
    tl -> tokenList.pop_front();
  }else if (currentToken.tokenType == keyword::NUMBER){
    cout << "LIT 0 " << currentToken.number << endl;
    tl -> tokenList.pop_front();
  }else if (currentToken.tokenType == keyword::PARENL){
    tl -> tokenList.pop_front();
    expression();
    currentToken = tl -> tokenList.front();
    // ERROR: No Closing Parenthesis
    if (currentToken.tokenType != keyword::PARENR){
      cout <<  "ERROR: No Closing Parenthesis"  << endl;
      exit(1);
    }
  }

  return 1;
}

int term(){

  Token currentToken = tl -> tokenList.front();

  factor();

  while(currentToken.tokenType == keyword::MULT || currentToken.tokenType == keyword::DIV){
    if (currentToken.tokenType == keyword::MULT){
      tl -> tokenList.pop_front();
      factor();
      emit(2,0,3);
      cout << "MULT 0 3";
    }else if (currentToken.tokenType == keyword::DIV){
      tl -> tokenList.pop_front();
      factor();
      emit(2,0,4);
      cout << "DIV 0 4";
  }
  }

  return 1;
}

int expression() {

  Token currentToken = tl -> tokenList.front();

  int sign = 1;
  if (currentToken.tokenType == keyword::SUB){
    sign = -1;
    tl -> tokenList.pop_front();
  } else if (currentToken.tokenType == keyword::ADD){
    tl -> tokenList.pop_front();
  }

  term();
  currentToken = tl -> tokenList.front();

  // If First Term is Negative
  if(sign == -1){
    emit(1, 0, -1);
    cout << "LIT 0 -1" << endl;
    emit(2, 0, 3);
    cout << "MULT 0 3" << endl;
  }

  // ADD or SUB
  while(currentToken.tokenType == keyword::ADD || currentToken.tokenType == keyword::SUB){
    if (currentToken.tokenType == keyword::ADD){
      tl -> tokenList.pop_front();
      term();
      emit(2, 0, 1);
      cout << "ADD 0 1 " << endl;
    }else if (currentToken.tokenType == keyword::SUB){
      tl -> tokenList.pop_front();
      term();
      emit(2, 0, 3);
      cout << "SUB 0 2" << endl;
    }

  currentToken = tl -> tokenList.front();
  }

 return 1;
}

int addString(string str){

  // Add string to string vector and return its position

  stringData.push_back(str);
  return stringData.size() - 1;

}

int expressionList(){

  Token currentToken = tl -> tokenList.front();

  // Check if an Expression or String
  if (currentToken.tokenType == keyword::STRING){

    cout<< "PRINT STRING \""<< currentToken.contents << "\"" << endl;
    cout << "SYS 1 " << addString(currentToken.contents) << endl;
    tl -> tokenList.pop_front();
    currentToken = tl -> tokenList.front();

  }else{

      cout << "PRINT EXPRESSION" << endl;
      expression();
      while(currentToken.tokenType != keyword::CR && currentToken.tokenType != keyword::COMMA && !tl -> tokenList.empty()){
        tl -> tokenList.pop_front();
        currentToken = tl -> tokenList.front();
      }
  }

    // At this point, the program is in a list of expression/strings or the end of the line
    // Check if there are more things to print
    // currentToken = tl -> tokenList.front();
    if(currentToken.tokenType == keyword::COMMA){

      while(currentToken.tokenType == keyword::COMMA){

        tl -> tokenList.pop_front();
        currentToken = tl -> tokenList.front();

        if (currentToken.tokenType == keyword::STRING){
          cout<< "PRINT STRING \""<< currentToken.contents << "\"" << endl;
          cout << "SYS 1 " << addString(currentToken.contents) << endl;
          tl -> tokenList.pop_front();
          currentToken = tl -> tokenList.front();
        }else{
          cout << "PRINT EXPRESSION" << endl;
          expression();
          currentToken = tl -> tokenList.front();
          while(currentToken.tokenType != keyword::CR && currentToken.tokenType != keyword::COMMA && !tl -> tokenList.empty()){
            tl -> tokenList.pop_front();
            currentToken = tl -> tokenList.front();
          }

        }

      }

    }


    return 1;
}


// Return or Put in generateIF functions
int relop(keyword rel){

  switch (rel) {
  case LSS:{emit(2,0,7); cout << "LSS 0 7" << endl;break;}
  case EQL:{ emit(2,0,5); cout << "EQL 0 5" << endl;break;}
  case NEQ:{ emit(2,0,6); cout << "NEQ 0 6" << endl;break;}
  case LEQ:{ emit(2,0,6); cout << "LEQ 0 8" << endl;break;}
  case GTR:{ emit(2,0,9); cout << "GTR 0 9" << endl;break;}
  case GEQ:{ emit(2,0,10); cout << "GEQ 0 10" << endl;break;}
  default:
    cout << "ERROR: Invalid Relative Operator" << endl;
    exit(1);
  }

 return 1;
}

//NOTE: The Need to complete the instruction vector so that the if statement can keep track of the line numbers
int generateIF(){

  // ====== Condition ======
  tl -> tokenList.pop_front();
  expression();


  //TODO: Have a Checker for relative operation
  keyword rel = tl -> tokenList.front().tokenType;
  tl -> tokenList.pop_front();

  expression();
  relop(rel);

  cout << "JPC 0 0" << endl;
  emit(8,0,0);


  // Save Location of JPC Command
  int jumpIndex = instructs.size();

  //====== Condition is finished =====
  Token currentToken = tl -> tokenList.front();

  if (currentToken.tokenType != keyword::THEN){
    cout << "ERROR: IF Statements must have Then Statements" << endl;
    exit(1);
  }

  tl -> tokenList.pop_front();
  genStatement();

  // If False, Go to Jump Address
  instructs[jumpIndex] = instructs.size();

  return 1;
}

int generatePRINT(){

  // Check for PRINT
  Token currentToken = tl -> tokenList.front();
  if (currentToken.tokenType != keyword::PRINT){
    cout << "ERROR: Print Statement Missing PRINT" << endl;
    exit(1);
  }

  tl -> tokenList.pop_front();
  // Detect List of Expressions and Strings
  expressionList();

return 1;
}

int genStatement(){

 Token currentToken = tl -> tokenList.front();
 switch (currentToken.tokenType) {

 case keyword::PRINT: {cout << "This is a PRINT Statement" << endl; generatePRINT(); break;}
 case keyword::IF: {cout << "This is a IF Statement" << endl; generateIF(); break;}
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

  // TODO: Hold Remember previous line numbers for non-numbered lines
  int lineNum = 0;
  if(tl ->tokenList.front().tokenType == keyword::NUMBER) {
    lineNum =tl ->tokenList.front().number;
    addLine(lineNum);
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

  // Line must end with a CR or END OF FILE
  if (tl ->tokenList.front().tokenType == keyword::CR ){
    tl -> tokenList.pop_front();
  }else if (!tl -> tokenList.empty()){
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

