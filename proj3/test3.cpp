// File: test3.cpp
//
// Simple test of inserting and removing.
// This test includes inserting duplicates and
// attempt to remove keys not in the tree.
//

#include <iostream>
using namespace std ;

#include "LazyBST.h"

int main() {

   LazyBST T ;

   T.insert(14) ;

   T.insert(7) ;
   T.insert(25) ;

   T.insert(3) ; T.insert(32) ; 
   T.insert(9) ; T.insert(18) ; 

// Inserting duplicates
  
   T.insert(3) ; T.insert(32) ; 
   T.insert(9) ; T.insert(18) ; 

   T.insert(1) ; T.insert(44) ;
   T.insert(12) ; T.insert(15) ; 
   T.insert(4) ; T.insert(29) ; 
   T.insert(10) ; T.insert(21) ;

   T.inorder() ; cout << endl ;

   cout << "removing ..." << endl; 
   int answer ;
//   T.dump() ;

   int n ;

   n = 14 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
   n = 12 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
   n =  7 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
   n = 25 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
   n =  3 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
   n = 29 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
   n = 32 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
   n = 15 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 


// Removing items that do not exist
   cout << endl ;
   n = 19 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
   n = 101 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
   n = -32 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
   cout << endl ;

   n = 18 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
   n = 21 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
   n = 10 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
   n =  9 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
   n =  1 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
   n = 44 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
   n =  4 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
}
