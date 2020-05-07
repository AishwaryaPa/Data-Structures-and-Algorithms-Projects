/*****************************************
 ** File:    Graph.cpp
 ** Project: CMSC 341 Project 1, Spring 2017
 ** Author:  Aishwarya Panchumarty
 ** Date:    02/16/17
 ** Section: 03
 ** E-mail:  aispan1@umbc.edu
 **
 **  Simple driver program to call the Sally Forth interpreter
 **  This version accepts user input for filename of Sally Forth
 **  source code.
 **
 ***********************************************/

#include <iostream>
#include <fstream>
using namespace std ;

#include "Sally.h"

int main() {
   string fname ;

   cout << "Enter file name: " ;
   cin >> fname ;
   ifstream ifile(fname.c_str()) ;

   Sally S(ifile) ;

   S.mainLoop() ;

   ifile.close() ;
   return 0 ;
}
