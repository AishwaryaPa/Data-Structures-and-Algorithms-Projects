// File: test2.cpp
//
// Simple test that also removes nodes.
//
// Should see rebalancing during remove.
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

   T.insert(1) ; T.insert(44) ;
   T.insert(12) ; T.insert(15) ; 
   T.insert(4) ; T.insert(29) ; 
   T.insert(10) ; T.insert(21) ;

   T.inorder() ; cout << endl ;

   cout << "removing ..." << endl; 
   //   T.dump() ;

   int n ;

   n = 44 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
   n = 32 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
   n = 29 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
   n = 21 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
   n = 18 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
   n = 25 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
   n = 15 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
   n = 14 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
   n = 12 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
   n = 10 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 
   n = 9 ; cout << "removing " << n << endl ; T.remove(n) ; T.inorder() ; cout << endl ; 

}
