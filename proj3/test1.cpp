// File: test1.cpp
// 
// Simple test of insertion
// Should see rebalance when inserting 33.

#include <iostream>
using namespace std ;

#include "LazyBST.h"

int main() {

   LazyBST T ;

   T.insert(70) ;
   T.inorder() ; cout << endl ; 

   T.insert(30) ;
   T.inorder() ; cout << endl ;

   T.insert(110) ;

   T.inorder() ; cout << endl ;

   cout << "\n\n***** Insert 40 *****\n" ;
   T.insert(40) ;
   T.inorder() ; cout << endl ;

   cout << "\n\n***** Insert 20 *****\n" ;
   T.insert(20) ;
   T.inorder() ; cout << endl ;

   cout << "\n\n***** Insert 41 *****\n" ;
   T.insert(41) ;
   T.inorder() ; cout << endl ;

   cout << "\n\n***** Insert 31 *****\n" ;
   T.insert(31) ;
   T.inorder() ; cout << endl ;

   cout << "\n\n***** Insert 32 *****\n" ;
   T.insert(32) ;
   T.inorder() ; cout << endl ;

   cout << "\n\n***** Insert 33 *****\n" ;
   T.insert(33) ;
   T.inorder() ; cout << endl ;

   cout << "\n\n***** Insert 19 *****\n" ;
   T.insert(19) ;
   T.inorder() ; cout << endl ;

   cout << "\n\n***** Insert 34 *****\n" ;
   T.insert(34) ;
   T.inorder() ; cout << endl ;

   cout << "\n\n***** Insert 15 *****\n" ;
   T.insert(15) ;
   T.inorder() ; cout << endl ;

   cout << "\n\n***** Insert 14 *****\n" ;
   T.insert(14) ;
   T.inorder() ; cout << endl ;
}
