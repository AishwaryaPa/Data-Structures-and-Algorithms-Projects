/*****************************************
 ** File:    Sally.cpp
 ** Project: CMSC 341 Project 2, Spring 2017
 ** Author:  Aishwarya Panchumarty
 ** Date:    03/07/17
 ** Section: 03
 ** E-mail:  aispan1@umbc.edu
 **
 ** This file contains the implementations
 ** of the functions in Sally.h.
 **
 ***********************************************/


#include <iostream>
#include <string>
#include <list>
#include <stack>
#include <stdexcept>
#include <cstdlib>
using namespace std ;

#include "Sally.h"


// Basic Token constructor. Just assigns values.
//
Token::Token(TokenKind kind, int val, string txt) {
   m_kind = kind ;
   m_value = val ;
   m_text = txt ;
}


// Basic SymTabEntry constructor. Just assigns values.
//
SymTabEntry::SymTabEntry(TokenKind kind, int val, operation_t fptr) {
   m_kind = kind ;
   m_value = val ;
   m_dothis = fptr ;
}


// Constructor for Sally Forth interpreter.
// Adds built-in functions to the symbol table.
//
Sally::Sally(istream& input_stream) :
   istrm(input_stream)  // use member initializer to bind reference
{

   symtab["DUMP"] =  SymTabEntry(KEYWORD,0,&doDUMP) ;

   symtab["+"]    =  SymTabEntry(KEYWORD,0,&doPlus) ;
   symtab["-"]    =  SymTabEntry(KEYWORD,0,&doMinus) ;
   symtab["*"]    =  SymTabEntry(KEYWORD,0,&doTimes) ;
   symtab["/"]    =  SymTabEntry(KEYWORD,0,&doDivide) ;
   symtab["%"]    =  SymTabEntry(KEYWORD,0,&doMod) ;
   symtab["NEG"]  =  SymTabEntry(KEYWORD,0,&doNEG) ;

   symtab["."]    =  SymTabEntry(KEYWORD,0,&doDot) ;
   symtab["SP"]   =  SymTabEntry(KEYWORD,0,&doSP) ;
   symtab["CR"]   =  SymTabEntry(KEYWORD,0,&doCR) ;

   symtab["DUP"]  =  SymTabEntry(KEYWORD,0,&doDUP) ;   
   symtab["DROP"] =  SymTabEntry(KEYWORD,0,&doDROP) ;
   symtab["SWAP"] =  SymTabEntry(KEYWORD,0,&doSWAP) ;
   symtab["ROT"]  =  SymTabEntry(KEYWORD,0,&doROT) ;

   symtab["SET"]  =  SymTabEntry(KEYWORD,0,&doSET) ;
   symtab["@"]    =  SymTabEntry(KEYWORD,0,&doAT) ;
   symtab["!"]    =  SymTabEntry(KEYWORD,0,&doEXC) ;


   symtab["<"]    =  SymTabEntry(KEYWORD,0,&compareLT) ;
   symtab["<="]   =  SymTabEntry(KEYWORD,0,&compareLTE) ;
   symtab["=="]   =  SymTabEntry(KEYWORD,0,&compareE) ;
   symtab["!="]   =  SymTabEntry(KEYWORD,0,&compareNE) ;
   symtab[">"]    =  SymTabEntry(KEYWORD,0,&compareGT) ;
   symtab[">="]   =  SymTabEntry(KEYWORD,0,&compareGTE) ;

   symtab["AND"]  =  SymTabEntry(KEYWORD,0,&doAND) ;
   symtab["OR"]   =  SymTabEntry(KEYWORD,0,&doOR) ;
   symtab["NOT"]  =  SymTabEntry(KEYWORD,0,&doNOT) ;

   symtab["IFTHEN"] =  SymTabEntry(KEYWORD,0,&doIFTHEN) ;
   symtab["ELSE"]   =  SymTabEntry(KEYWORD,0,&doELSE) ;
   symtab["ENDIF"]  =  SymTabEntry(KEYWORD,0,&doENDIF) ;
 
   symtab["DO"]     =  SymTabEntry(KEYWORD,0,&doDO) ;
   symtab["UNTIL"]  =  SymTabEntry(KEYWORD,0,&doUNTIL) ;

}


// This function should be called when tkBuffer is empty.
// It adds tokens to tkBuffer.
//
// This function returns when an empty line was entered 
// or if the end-of-file has been reached.
//
// This function returns false when the end-of-file was encountered.
// 
// Processing done by fillBuffer()
//   - detects and ignores comments.
//   - detects string literals and combines as 1 token
//   - detetcs base 10 numbers
// 
//
bool Sally::fillBuffer() {
   string line ;     // single line of input
   int pos ;         // current position in the line
   int len ;         // # of char in current token
   long int n ;      // int value of token
   char *endPtr ;    // used with strtol()


   while(true) {    // keep reading until empty line read or eof

      // get one line from standard in
      //
      getline(istrm, line) ;   

      // if "normal" empty line encountered, return to mainLoop
      //
      if ( line.empty() && !istrm.eof() ) {
         return true ;
      }

      // if eof encountered, return to mainLoop, but say no more
      // input available
      //
      if ( istrm.eof() )  {
         return false ;
      }


      // Process line read

      pos = 0 ;                      // start from the beginning

      // skip over initial spaces & tabs
      //
      while( line[pos] != '\0' && (line[pos] == ' ' || line[pos] == '\t') ) {
         pos++ ; 
      }

      // Keep going until end of line
      //
      while (line[pos] != '\0') {

         // is it a comment?? skip rest of line.
         //
         if (line[pos] == '/' && line[pos+1] == '/') break ;

         // is it a string literal? 
         //
         if (line[pos] == '.' && line[pos+1] == '"') {

            pos += 2 ;  // skip over the ."
            len = 0 ;   // track length of literal

            // look for matching quote or end of line
            //
            while(line[pos+len] != '\0' && line[pos+len] != '"') {
               len++ ;
            }

            // make new string with characters from
            // line[pos] to line[pos+len-1]
            string literal(line,pos,len) ;  // copy from pos for len chars

            // Add to token list
            //
            tkBuffer.push_back( Token(STRING,0,literal) ) ;  

            // Different update if end reached or " found
            //
            if (line[pos+len] == '\0') {
               pos = pos + len ;
            } else {
               pos = pos + len + 1 ;
            }

         } else {  // otherwise "normal" token

            len = 0 ;  // track length of token

            // line[pos] should be an non-white space character
            // look for end of line or space or tab
            //
            while(line[pos+len] != '\0' && line[pos+len] != ' ' && line[pos+len] != '\t') {
               len++ ;
            }

            string literal(line,pos,len) ;   // copy form pos for len chars
            pos = pos + len ;

            // Try to convert to a number
            //
            n = strtol(literal.c_str(), &endPtr, 10) ;

            if (*endPtr == '\0') {
               tkBuffer.push_back( Token(INTEGER,n,literal) ) ;
            } else {
               tkBuffer.push_back( Token(UNKNOWN,0,literal) ) ;
            }
         }

         // skip over trailing spaces & tabs
         //
         while( line[pos] != '\0' && (line[pos] == ' ' || line[pos] == '\t') ) {
            pos++ ; 
         }

      }
   }
}



// Return next token from tkBuffer.
// Call fillBuffer() if needed.
// Checks for end-of-file and throws exception 
//
Token Sally::nextToken() {
      Token tk ;
      bool more = true ;

      while(more && tkBuffer.empty() ) {
         more = fillBuffer() ;
      }

      if ( !more && tkBuffer.empty() ) {
         throw EOProgram("End of Program") ;
      }

      tk = tkBuffer.front() ;
      tkBuffer.pop_front() ;
      return tk ;
}


// The main interpreter loop of the Sally Forth interpreter.
// It gets a token and either push the token onto the parameter
// stack or looks for it in the symbol table.
//
//
void Sally::mainLoop() {

   Token tk ;
   map<string,SymTabEntry>::iterator it ;

   try {
      while( 1 ) {
         tk = nextToken() ;

         if (tk.m_kind == INTEGER || tk.m_kind == STRING) {

            // if INTEGER or STRING just push onto stack
            params.push(tk) ;

         } else { 
            it = symtab.find(tk.m_text) ;
            
            if ( it == symtab.end() )  {   // not in symtab

               params.push(tk) ;

            } else if (it->second.m_kind == KEYWORD)  {

               // invoke the function for this operation
               //
               it->second.m_dothis(this) ;   
               
            } else if (it->second.m_kind == VARIABLE) {

               // variables are pushed as tokens
               //
               tk.m_kind = VARIABLE ;
               params.push(tk) ;

            } else {

               // default action
               //
               params.push(tk) ;

            }
         }
      }

   } catch (EOProgram& e) {
     
     cerr << "End of Program\n" ;
      if ( params.size() == 0 ) {
         cerr << "Parameter stack empty.\n" ;
      } else {
         cerr << "Parameter stack has " << params.size() << " token(s).\n" ;
      }

   } catch (out_of_range& e) {

      cerr << "Parameter stack underflow??\n" ;

   } catch (...) {

      cerr << "Unexpected exception caught\n" ;

   }
}

// -------------------------------------------------------

// doPlus
// Adds the two top values from the stack and pushes
// the answer to the stack
void Sally::doPlus(Sally *Sptr) {
   Token p1, p2 ;

   if ( Sptr->params.size() < 2 ) {
      throw out_of_range("Need two parameters for +.") ;
   }

   p1 = Sptr->params.top() ;
   Sptr->params.pop() ;
   p2 = Sptr->params.top() ;
   Sptr->params.pop() ;

   int answer = p2.m_value + p1.m_value ;
   Sptr->params.push( Token(INTEGER, answer, "") ) ;
}

// doMinus
// Subtracts the two top values from the stack and pushes
// the answer to the stack
void Sally::doMinus(Sally *Sptr) {
   Token p1, p2 ;

   if ( Sptr->params.size() < 2 ) {
      throw out_of_range("Need two parameters for -.") ;
   }

   p1 = Sptr->params.top() ;
   Sptr->params.pop() ;
   p2 = Sptr->params.top() ;
   Sptr->params.pop() ;

   int answer = p2.m_value - p1.m_value ;
   Sptr->params.push( Token(INTEGER, answer, "") ) ;
}

// doTimes
// Multiplies the two top values from the stack and pushes
// the answer to the stack
void Sally::doTimes(Sally *Sptr) {
   Token p1, p2 ;

   if ( Sptr->params.size() < 2 ) {
      throw out_of_range("Need two parameters for *.") ;
   }

   p1 = Sptr->params.top() ;
   Sptr->params.pop() ;
   p2 = Sptr->params.top() ;
   Sptr->params.pop() ;

   int answer = p2.m_value * p1.m_value ;
   Sptr->params.push( Token(INTEGER, answer, "") ) ;
}

// doDivide
// Divides the two top values from the stack and pushes
// the answer to the stack
void Sally::doDivide(Sally *Sptr) {
   Token p1, p2 ;

   if ( Sptr->params.size() < 2 ) {
      throw out_of_range("Need two parameters for /.") ;
   }

   p1 = Sptr->params.top() ;
   Sptr->params.pop() ;
   p2 = Sptr->params.top() ;
   Sptr->params.pop() ;

   int answer = p2.m_value / p1.m_value ;
   Sptr->params.push( Token(INTEGER, answer, "") ) ;
}

// doMod
// Takes mod of  the two top values from the stack and pushes
// the answer to the stack
void Sally::doMod(Sally *Sptr) {
   Token p1, p2 ;

   if ( Sptr->params.size() < 2 ) {
      throw out_of_range("Need two parameters for %.") ;
   }

   p1 = Sptr->params.top() ;
   Sptr->params.pop() ;
   p2 = Sptr->params.top() ;
   Sptr->params.pop() ;

   int answer = p2.m_value % p1.m_value ;
   Sptr->params.push( Token(INTEGER, answer, "") ) ;
}

// doNEG
// Multiplies the last value on the stack with -1 and pushes
// the answer to the stack
void Sally::doNEG(Sally *Sptr) {
   Token p ;

   if ( Sptr->params.size() < 1 ) {
      throw out_of_range("Need one parameter for NEG.") ;
   }

   p = Sptr->params.top() ;
   Sptr->params.pop() ;

   Sptr->params.push( Token(INTEGER, -p.m_value, "") ) ;
}

// doDot
// Prints the last value on the stack
void Sally::doDot(Sally *Sptr) {
   Token p ;

   if ( Sptr->params.size() < 1 ) {
      throw out_of_range("Need one parameter for .") ;
   }

   p = Sptr->params.top() ;
   Sptr->params.pop() ;

   if (p.m_kind == INTEGER) {
      cout << p.m_value ;

   } else {
      cout << p.m_text ;
   }
}

// doSP
// Prints a space
void Sally::doSP(Sally *Sptr) {
   cout << " " ;
}

// doCR
// Ends a line
void Sally::doCR(Sally *Sptr) {
   cout << endl ;
}

void Sally::doDUMP(Sally *Sptr) {
   // do whatever for debugging
}

// doSet()
// Assigns a string to an integer and adds that string to the symbol table
// to be refered later. Does not allow duplicate variables to be made
void Sally::doSET(Sally *Sptr) {
  Token p1, p2 ;
 
  if ( Sptr->params.size() < 2 ) {
    throw out_of_range("Need two parameters for SET.") ;
  }

  p1 = Sptr->params.top() ;
  Sptr->params.pop() ;
  p2 = Sptr->params.top() ;
  Sptr->params.pop() ;

  if (p1.m_kind != STRING){
    throw out_of_range("Variable must be a string");
  }

  if (p2.m_kind != INTEGER){
    throw out_of_range("Variable must be assigned to only integers");
  }

  map<string,SymTabEntry>::iterator it ;
  it = Sptr->symtab.find(p1.m_text) ;

  if ( it == Sptr->symtab.end() )  {   // not in symtab

    SymTabEntry p3 = SymTabEntry(VARIABLE, p2.m_value, NULL) ;
    Sptr->symtab.insert(std::pair<string,SymTabEntry>(p1.m_text, p3));

  } 

  else {
    throw out_of_range("Duplicate definitions are not allowed") ;
  }

}

// doAT()
// Fetches the values of a given variable. If the variable
// does not exist, then an exception is thrown
void Sally::doAT(Sally *Sptr) {
  if ( Sptr->params.size() < 1 ) {
    throw out_of_range("Need one parameter for @.") ;
  }
  
  Token p1 = Sptr->params.top() ;
  Sptr->params.pop() ;

  int answer = 0;

  map<string,SymTabEntry>::iterator it ;
  it = Sptr->symtab.find(p1.m_text) ;

  if ( it == Sptr->symtab.end() )  {  
    throw out_of_range("Variable does not exist") ;
  }

  else {

    SymTabEntry p2 = it->second;
    answer = p2.m_value;
    Sptr->params.push( Token(INTEGER, answer, " ") ) ;

  }

}

// doEXC()
// Reassigns the variable in the symbol table to another value 
void Sally::doEXC(Sally *Sptr) {
  Token p1, p2 ;

  if ( Sptr->params.size() < 2 ) {
    throw out_of_range("Need two parameters for EXC.") ;
  }

  p1 = Sptr->params.top() ;
  Sptr->params.pop() ;
  p2 = Sptr->params.top() ;
  Sptr->params.pop() ;

  map<string,SymTabEntry>::iterator it ;
  it = Sptr->symtab.find(p1.m_text) ;

  if ( it == Sptr->symtab.end() )  {   // not in symtab
    throw out_of_range("Variable does not exist") ;
  } 

  else{
    it->second.m_value = p2.m_value;
  }
  
}

// doDup()
// Creates a duplicate token and adds it to the stack
void Sally::doDUP(Sally *Sptr){
  Token p1 ;

  if ( Sptr->params.size() < 1 ) {
    throw out_of_range("Need atleast one parameter for DUP.") ;
  }

  p1 = Sptr->params.top() ;

  int copy = p1.m_value ;
  Sptr->params.push( Token(INTEGER, copy, "") ) ;
  
}

// doDrop()
// Pops off the value at the top of stack
void Sally::doDROP(Sally *Sptr) {
  if ( Sptr->params.size() < 1 ) {
    throw out_of_range("Need one parameter for DROP.") ;
  }

  Sptr->params.pop() ;

}

// doSwap()
// Swaps the two tokens at the top of the stack
void Sally::doSWAP(Sally *Sptr) {
  Token p1, p2 ;

  if ( Sptr->params.size() < 2 ) {
    throw out_of_range("Need two parameters for SWAP.") ;
  }

  p1 = Sptr->params.top() ;
  Sptr->params.pop() ;
  p2 = Sptr->params.top() ;
  Sptr->params.pop() ;
 
  int firstNum = p1.m_value ;
  int secondNum = p2.m_value ;

  Sptr->params.push( Token(INTEGER, secondNum, "") ) ;
  Sptr->params.push( Token(INTEGER, firstNum, "") ) ;

}

// doRot()
// Rotates three variables at the top of the stack and pushes
// them back on the stack
void Sally::doROT(Sally *Sptr) {
  Token p1, p2, p3 ;

  if ( Sptr->params.size() < 3 ) {
    throw out_of_range("Need three parameters for ROT.") ;
  }

  p1 = Sptr->params.top() ;
  Sptr->params.pop() ;
  p2 = Sptr->params.top() ;
  Sptr->params.pop() ;
  p3 = Sptr->params.top() ;
  Sptr->params.pop() ;

  int firstNum = p1.m_value ;
  int secondNum = p2.m_value ;
  int thirdNum = p3.m_value ;

  Sptr->params.push( Token(INTEGER, secondNum, "") ) ;
  Sptr->params.push( Token(INTEGER, firstNum, "") ) ;
  Sptr->params.push( Token(INTEGER, thirdNum, "") ) ;

}

// compareLT()
// Compares two values given at the top of the stack. If the second
// value is less than the first one, 1 will pushed on the stack 
// otherwise 0.  
void Sally::compareLT(Sally *Sptr){
  Token p1, p2 ;

  if ( Sptr->params.size() < 2 ) {
    throw out_of_range("Need two parameters for <.") ;
  }

  p1 = Sptr->params.top() ;
  Sptr->params.pop() ;
  p2 = Sptr->params.top() ;
  Sptr->params.pop() ;

  int answer;
  if (p2.m_value < p1.m_value){
    answer = 1;
  }

  else {
    answer = 0;
  }

  Sptr->params.push( Token(INTEGER, answer, "") ) ;
}

// compareLTE()
// Compares two values given at the top of the stack. If the second
// value is less than or equal to the first one, 1 will pushed on the stack
// otherwise 0.
void Sally::compareLTE(Sally *Sptr) {
  Token p1, p2 ;

  if ( Sptr->params.size() < 2 ) {
    throw out_of_range("Need two parameters for <=.") ;
  }

  p1 = Sptr->params.top() ;
  Sptr->params.pop() ;
  p2 = Sptr->params.top() ;
  Sptr->params.pop() ;

  int answer;

  if (p2.m_value <= p1.m_value){
    answer = 1;
  }

  else {
    answer = 0;
  }

  Sptr->params.push( Token(INTEGER, answer, "") ) ;

}

// compareE()
// Compares two values given at the top of the stack. If the second
// value is equal to  first one, 1 will pushed on the stack
// otherwise 0.
void Sally::compareE(Sally *Sptr) {
  Token p1, p2 ;

  if ( Sptr->params.size() < 2 ) {
    throw out_of_range("Need two parameters for <.") ;
  }

  p1 = Sptr->params.top() ;
  Sptr->params.pop() ;
  p2 = Sptr->params.top() ;
  Sptr->params.pop() ;

  int answer;

  if (p2.m_value == p1.m_value){
    answer = 1;
  }

  else {
    answer = 0;
  }

  Sptr->params.push( Token(INTEGER, answer, "") ) ;

}

// compareNE()
// Compares two values given at the top of the stack. If the second
// value is not equal to the first one, 1 will pushed on the stack
// otherwise 0.
void Sally::compareNE(Sally *Sptr){
  Token p1, p2 ;

  if ( Sptr->params.size() < 2 ) {
    throw out_of_range("Need two parameters for <.") ;
  }

  p1 = Sptr->params.top() ;
  Sptr->params.pop() ;
  p2 = Sptr->params.top() ;
  Sptr->params.pop() ;

  int answer;

  if (p2.m_value != p1.m_value){
    answer = 1;
  }

  else {
    answer = 0;
  }

  Sptr->params.push( Token(INTEGER, answer, "") ) ;

}

// compareGT()
// Compares two values given at the top of the stack. If the second
// value is greater than the first one, 1 will pushed on the stack
// otherwise 0.
void Sally::compareGT(Sally *Sptr) {
  Token p1, p2 ;

  if ( Sptr->params.size() < 2 ) {
    throw out_of_range("Need two parameters for <.") ;
  }

  p1 = Sptr->params.top() ;
  Sptr->params.pop() ;
  p2 = Sptr->params.top() ;
  Sptr->params.pop() ;

  int answer;

  if (p2.m_value > p1.m_value){
    answer = 1;
  }

  else {
    answer = 0;
  }

  Sptr->params.push( Token(INTEGER, answer, "") ) ;

}

// compareGTE()
// Compares two values given at the top of the stack. If the second
// value is greater than or equal to the first one, 1 will pushed on the stack
// otherwise 0.
void Sally::compareGTE(Sally *Sptr) {
  Token p1, p2 ;

  if ( Sptr->params.size() < 2 ) {
    throw out_of_range("Need two parameters for <.") ;
  }

  p1 = Sptr->params.top() ;
  Sptr->params.pop() ;
  p2 = Sptr->params.top() ;
  Sptr->params.pop() ;

  int answer;
  if (p2.m_value >= p1.m_value){
    answer = 1;
  }

  else {
    answer = 0;
  }

  Sptr->params.push( Token(INTEGER, answer, "") ) ;

}

// doAND()
// If both values at the top of the stack are true (greater than or equal to one)
// then 1 will be pushed on the stack. Otherwise zero.
void Sally::doAND(Sally *Sptr){
  Token p1, p2 ;

  if ( Sptr->params.size() < 2 ) {
    throw out_of_range("Need two parameters for AND") ;
  }

  p1 = Sptr->params.top() ;
  Sptr->params.pop() ;
  p2 = Sptr->params.top() ;
  Sptr->params.pop() ;

  int answer;

  if (p1.m_value >= 1 and p2.m_value >= 1){
    answer = 1;
  }

  else {
    answer = 0;
  }

  Sptr->params.push( Token(INTEGER, answer, "") ) ;

}

// doOR()
// If one of values at the top of the stack is true (greater than or equal to one)
// then 1 will be pushed on the stack. Otherwise zero.
void Sally::doOR(Sally *Sptr) {
  Token p1, p2 ;

  if ( Sptr->params.size() < 2 ) {
    throw out_of_range("Need two parameters for OR") ;
  }

  p1 = Sptr->params.top() ;
  Sptr->params.pop() ;
  p2 = Sptr->params.top() ;
  Sptr->params.pop() ;

  int answer;

  if (p1.m_value >= 1 or p2.m_value >= 1){
    answer = 1;
  }

  else {
    answer = 0;
  }

  Sptr->params.push( Token(INTEGER, answer, "") ) ;

}

// doNOT()
// If a value at the top of the stack is false (zero)
// then 1 will be pushed on the stack. Otherwise zero.
void Sally::doNOT(Sally *Sptr) {
  Token p1;

  if ( Sptr->params.size() < 1 ) {
    throw out_of_range("Need at least parameter for NOT.") ;
  }

  p1 = Sptr->params.top() ;
  Sptr->params.pop() ;

  int answer;

  if (p1.m_value == 0){
    answer = 1;
  }

  else {
    answer = 0;
  }

  Sptr->params.push( Token(INTEGER, answer, "") ) ;

}

// doIFTHEN()
// Executes the IFTHEN statements. If the IFTHEN statement is true,
// then this function will be called, but it will do not do anyting.
// Control is given to the main loop. If the IFTHEN statement is false,
// then this function will skip the block of code underneath it until
// the ELSE statement is reached
void Sally::doIFTHEN(Sally *Sptr) {
  Token p1;

  if ( Sptr->params.size() < 1 ) {
    throw out_of_range("Need at least parameter for IFTHEN.") ;
  }

  p1 = Sptr->params.top() ;

  if (p1.m_value == 0){

    Token tk ;
    int ifCount = 1;
    int elseCount = 0;
    bool stop = false;
    
    while( stop != true ) {

      tk = Sptr->nextToken() ;
      
      if (tk.m_text == "IFTHEN"){

	ifCount = ifCount + 1;
	Sptr->params.push(tk) ;
	Sptr->params.pop() ;

      } 
      
      else if(tk.m_text == "ELSE") {

	elseCount = elseCount + 1;
	Sptr->params.push(tk) ;
	Sptr->params.pop() ;
	
	
	if (ifCount == elseCount){
	  stop = true;
	}
      }
      
      else{

	Sptr->params.push(tk) ;
	Sptr->params.pop() ;

      }

    }
  }
}

// doELSE()
// Executes the ELSE statements. If the ELSE statement is true,
// then this function will be called, but it will do not do anyting.
// Control is given to the main loop. If the ELSE statement is false,
// then this function will skip the block of code underneath it until
// the ENDIF statement is reached, and delete the tokens left on the stack.
void Sally::doELSE(Sally *Sptr) {
  Token tk ;

  int elseCount = 1;
  int endIfCount = 0;
  bool stop = false;
  
  while( stop != true ) {

    tk = Sptr->nextToken() ;
    
    if (tk.m_text == "ELSE"){

      elseCount = elseCount + 1;
      Sptr->params.push(tk) ;
      Sptr->params.pop() ;

    }
    
    else if(tk.m_text == "ENDIF") {

      endIfCount = endIfCount + 1;
      if (elseCount == endIfCount){

	Sptr->doENDIF(Sptr);
        stop = true;

      }

      else{

	Sptr->params.push(tk) ;
	Sptr->params.pop() ;

      }

    }
  }
}

// doENDIF()
// Empties the stack. 
void Sally::doENDIF(Sally *Sptr) {
  Token p1 ;

  while(!Sptr->params.empty()){

    p1 = Sptr->params.top() ;
    Sptr->params.pop() ;

  }

}

// doDO()
// Saves all the token in tkBuffer and a temp list
void Sally::doDO(Sally *Sptr){
  if ( Sptr->params.size() < 1 ) {
    throw out_of_range("Need at least parameter for DO.") ;
  }

  // Save tokens 
  Token p1 ;
  bool stop = false;
  while( stop != true ) {
    p1 = Sptr->nextToken() ;
    
    if (p1.m_text == "UNTIL"){
      Sptr->tkBuffer.push_back(p1);
      Sptr->temp.push_back(p1);
      stop = true;
    }
    else{
      Sptr->tkBuffer.push_back(p1);
      Sptr->temp.push_back(p1);
    }
  }
  
} 
  

// doUNTIL()
// Exectes the code underneath the do statement
// until the statement is true
void Sally::doUNTIL(Sally *Sptr){
  Token p1;

  if ( Sptr->params.size() < 1 ) {
    throw out_of_range("Need at least parameter for UNTIL.") ;
  }

  p1 = Sptr->params.top() ;
  Sptr->params.pop() ;

  if (p1.m_value == 0){

    Token tk;
    list<Token>::iterator it;
    for (it = Sptr->temp.begin(); it != Sptr->temp.end(); it++){
      Token tk = *it;
      Sptr->tkBuffer.push_back(tk);
    }
  }

  else if(p1.m_value == 1){
    Sptr->tkBuffer.clear();
    Sptr->temp.clear();
  }
}


