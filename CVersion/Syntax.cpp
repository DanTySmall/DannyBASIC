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

void printCode(){

  cout << "===== Code Output =====" << endl;
  string instructNames[9];

  // print All the Numbers
  int size = instructs.size();
  for (int i = 0; i < size; i += 3) {

    cout << i << ": ";

    switch (instructs[i]) {
    case 1: cout << "LIT "; break;
    case 2:
      switch (instructs[i+2]) {
      case 0: cout << "RTN "; break;
      case 1: cout << "ADD "; break;
      case 2: cout << "SUB "; break;
      case 3: cout << "MULT "; break;
      case 4: cout << "DIV "; break;
      case 5: cout << "EQL "; break;
      case 6: cout << "NEQ "; break;
      case 7: cout << "LSS "; break;
      case 8: cout << "LEQ "; break;
      case 9: cout << "GTR "; break;
      case 10: cout << "GEQ "; break;
      }break;

    case 3: cout << "LOD "; break;
    case 4: cout << "STO "; break;
    case 5: cout << "CAL "; break;
    case 6: cout << "INC "; break;
    case 7: cout << "JMP "; break;
    case 8: cout << "JPC "; break;
    case 9:
      switch (instructs[i+2]) {
      case 0: cout << "SOU "; break;
      case 1: cout << "SIN "; break;
      case 2: cout << "HLT "; break;
      }break;
    }

    cout << instructs[i+1] << " " << instructs[i+2] << endl;
  }

}

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
  // cout << "Line Numbers: ";
  for(int i = 0; i < size; i++){

    // Place New Line Address before
    if(lineNums[i].lineNum == lineNum){
      // cout << lineNums[i].lineNum << " ";
      found = true;
      return lineNums[i].instructPtr;
    }

  }
    cout << endl;

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

    emit(3,0,currentToken.name.at(0) - 'A');
    cout << "LOD 0 " << (int)(currentToken.name.at(0) - 'A') << endl;
    tl -> tokenList.pop_front();
  }else if (currentToken.tokenType == keyword::NUMBER){
    emit(1,0,currentToken.number);
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

  currentToken = tl -> tokenList.front();
  while(currentToken.tokenType == keyword::MULT || currentToken.tokenType == keyword::DIV){
    if (currentToken.tokenType == keyword::MULT){
      tl -> tokenList.pop_front();
      factor();
      emit(2,0,3);
      cout << "MULT 0 3" << endl;
    }else if (currentToken.tokenType == keyword::DIV){
      tl -> tokenList.pop_front();
      factor();
      emit(2,0,4);
      cout << "DIV 0 4" << endl;
    }

    currentToken = tl -> tokenList.front();

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

int generateGOTO(){

  if (tl -> tokenList.front().tokenType != GOTO) {
    cout << "ERROR: INVALID GOTO STATEMENT";
    exit(1);
  }

  tl -> tokenList.pop_front();
  expression();

  // NOTE: New Commnad ( Jumps to Line Number at Top of Stack )
  emit(7,1, 0);
  cout << "JMP 1 0" << endl;

  return 1;
}

int varList(){

  Token currentToken = tl -> tokenList.front();
  if (currentToken.tokenType != ID) {
    cout << "ERROR: INVALID VAR LIST";
    exit(1);
  }

  cout << "SYS 0 2" << endl;
  emit(9,0,2);
  cout << "STO 0 " << (currentToken.name.at(0) - 'A') <<  endl;
  emit(4,0,(currentToken.name.at(0) - 'A'));

  tl -> tokenList.pop_front();

  currentToken = tl -> tokenList.front();
  while (currentToken.tokenType == COMMA){

    tl -> tokenList.pop_front();
    currentToken = tl -> tokenList.front();

    if (currentToken.tokenType != ID) {
      cout << "ERROR: INVALID VAR LIST";
      exit(1);
    }

    cout << "SYS 0 2" << endl;
    emit(9,0,2);
    cout << "STO 0 " << (currentToken.name.at(0) - 'A') <<  endl;
    emit(4,0,(currentToken.name.at(0) - 'A'));

    tl -> tokenList.pop_front();
    currentToken = tl -> tokenList.front();
  }

  return 1;
}

int generateINPUT(){


  if (tl -> tokenList.front().tokenType != INPUT) {
    cout << "ERROR: INVALID INPUT STATEMENT";
    exit(1);
  }


  varList();


  return 1;
}

int generateLET(){


  if (tl -> tokenList.front().tokenType != LET) {
    cout << "ERROR: INVALID LET STATEMENT";
    exit(1);
  }

  tl -> tokenList.pop_front();

  if (tl -> tokenList.front().tokenType != ID) {
    cout << "ERROR: MISSING VARIABLE IN ASSIGMENT";
    exit(1);
  }

  int var = tl -> tokenList.front().name.at(0) - 'A';

  tl -> tokenList.pop_front();

  if (tl -> tokenList.front().tokenType != EQL) {
    cout << "ERROR: MISSING VARIABLE IN ASSIGMENT";
    exit(1);
  }

  tl -> tokenList.pop_front();

  expression();
  emit(4,0,var);
  cout << "STO 0 " << var << endl;

  return 1;
}

int generateGOSUB() {



  if (tl -> tokenList.front().tokenType != GOSUB) {
    cout << "ERROR: INVALID GOSUB STATEMENT";
    exit(1);
  }

  tl -> tokenList.pop_front();

  expression();
  emit(5,0,0);
  cout<< "CAL 0 0" << endl;
  emit(6,0,2);
  cout<< "INC 0 2" << endl;

  return 1;
}

int generateRETURN(){

  if (tl -> tokenList.front().tokenType != RETURN) {
    cout << "ERROR: INVALID RETURN STATEMENT";
    exit(1);
  }

  tl -> tokenList.pop_front();

  emit(2,0,0);
  cout << "RTN 0 0" << endl;

 return 1;
}

int generateCLEAR(){


  if (tl -> tokenList.front().tokenType != CLEAR) {
    cout << "ERROR: INVALID CLEAR STATEMENT";
    exit(1);
  }

  tl -> tokenList.pop_front();


  for(int i = 0; i < 26; i++ ){


    emit (1,0,0);
    cout << "LIT 0 0" << endl;
    emit (4,0,i);
    cout << "STO 0 " << i << endl;
  }

  return 1;
}

// SUSPENDED: TO BE COMPLETED ON A LATER DAY
int generateRUN(){
// NOTE: RUN with Line Number will be handled on a different day

  if (tl -> tokenList.front().tokenType != RUN) {
    cout << "ERROR: INVALID RUN STATEMENT";
    exit(1);
  }

  tl -> tokenList.pop_front();

  // If Line includes Line number
  if (tl -> tokenList.front().tokenType != CR) {
    cout << "ERROR: RUN COMMANDS WITH LINE NUMBERS ARE NOT SUPPORTED";
    exit(1);
  }

  return 1;
}

int generateEND(){


  if (tl -> tokenList.front().tokenType != END) {
    cout << "ERROR: INVALID END STATEMENT";
    exit(1);
  }

  tl -> tokenList.pop_front();


  emit(9,0,3);
  cout << "SYS 0 3" << endl;

 return 1;
}

int genStatement(){

 Token currentToken = tl -> tokenList.front();
 switch (currentToken.tokenType) {

 case keyword::PRINT: {cout << "This is a PRINT Statement" << endl; generatePRINT(); break;}
 case keyword::IF: {cout << "This is a IF Statement" << endl; generateIF(); break;}
 case keyword::GOTO: {cout << "This is a GOTO Statement" << endl; generateGOTO(); break;}
 case keyword::INPUT: {cout << "This is a INPUT Statement" << endl; generateINPUT(); break;}
 case keyword::LET: {cout << "This is a LET Statement" << endl; generateLET(); break;}
 case keyword::GOSUB: {cout << "This is a GOSUB Statement" << endl; generateGOSUB(); break;}
 case keyword::RETURN: {cout << "This is a RETURN Statement" << endl; generateRETURN(); break;}
 case keyword::CLEAR: {cout << "This is a CLEAR Statement" << endl; generateCLEAR(); break;}
 // case keyword::LIST: {cout << "This is a LIST Statement" << endl; break;} // FOR INTERPRETER VERSION
 case keyword::RUN: {cout << "This is a RUN Statement" << endl; generateRUN(); return 1; break;}
 case keyword::END: {cout << "This is a END Statement" << endl; generateEND(); break;}
 default: {cout << "ERROR: String cant be parsed"; exit(1);}

 }



  return 0;

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

  if (genStatement()) return 1;



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

    if(line()) break;
    cout << endl;
  }

  cout << endl;

  return 0;
};

