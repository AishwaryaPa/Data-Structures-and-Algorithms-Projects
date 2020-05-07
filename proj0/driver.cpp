// File: driver.cpp
//
// CMSC 341 Spring 2017 Project 0
//
// Main program for knock-knock jokes
//

#include <string>
#include <iostream>
#include "joke.h"

using namespace std ;

int main() {

  cout << opening() << endl ;
  cout << "Who's there?" << endl ;
  cout << setup() << endl ;
  cout << setup() << ", who???" <<  endl ;
  cout << punchline() << endl ;

  return 0 ;
}
