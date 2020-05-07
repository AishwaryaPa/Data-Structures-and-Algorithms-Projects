// File: proj0test.cpp
//
// CMSC 341 Spring 2017 Project 0
//
// main() function used for grading
//


#include <iostream>
#include <string>
using namespace std ;

#include "joke.h"

int main() {

   // Store output from student's functions

   string str1(opening()) ;
   string str2(setup()) ;
   string str3(punchline()) ;

   string result ;   // string for comments

   int points = 100 ;  // max score


   // check each string is not empty

   if (str1.length() > 0) {
      result = "Testing opening string ... passed\n" ;
   } else {
      result = "Opening string is empty -8pts\n" ;
      points -= 8 ;
   }

   if (str2.length() > 0) {
      result.append("Testing setup string ... passed\n") ;
   } else {
      result.append("Setup string is empty -8pts\n") ;
      points -= 8 ;
   }

   if (str3.length() > 0) {
      result.append("Testing punchline ... passed\n") ;
   } else {
      result.append("Punchline is empty -8pts\n") ;
      points -= 8 ;
   }


   // Print out scores

   cout << "Raw grade: " << points << endl ;
   cout << "Late penalty: 0\n" ;
   cout << "Total grade: " << points << endl ;

   cout << "\n\n------------------------------------------------\n\n" ;

   cout << "Opening    = \"" << str1 << "\"\n" ;
   cout << "Setup      = \"" << str2 << "\"\n" ;
   cout << "Punchline  = \"" << str3 << "\"\n" ;

   cout << "\nResults of testing:\n\n" ;
   cout << result << endl ;


   // Check for originalilty

   if (str1 == "Knock, knock" && str2 == "Amos" 
            && str3 == "A mosquito bit me!")  {
      cout << "Don't you know any other knock-knock jokes???\n\n" ;
   }

   return 0 ;
}

