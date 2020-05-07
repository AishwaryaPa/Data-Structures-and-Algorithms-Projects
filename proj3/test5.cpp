// File: test5.cpp
//
// Tests copy constructor, destructor and assignment operator
//
// Should test this with valgrind
//

#include <iostream>
using namespace std ;

#include "LazyBST.h"

int main() {

   LazyBST T1 ;

   T1.insert(14) ;

   T1.insert( 7) ;
   T1.insert(25) ;

   T1.insert( 3) ; T1.insert(32) ; 
   T1.insert( 9) ; T1.insert(18) ; 

   T1.insert( 1) ; T1.insert(44) ;
   T1.insert(12) ; T1.insert(15) ; 
   T1.insert( 4) ; T1.insert(29) ; 
   T1.insert(10) ; T1.insert(21) ;

   cout << "Original T1:         " ;
   T1.inorder() ; cout << endl ;

   // Use copy constructor
   LazyBST *Tptr = new LazyBST(T1) ;

   cout << "Copied T1:           " ;
   Tptr->inorder() ; cout << endl; 
   
   LazyBST T2 ;

   /*   T2.insert(50) ;
   T2.insert(25) ; T2.insert(75) ;
   T2.inorder() ; cout << endl ;
   */
   T2 = *Tptr ;
   cout << "Second copy:         " ;
   T2.inorder() ; cout << endl ; 

   cout << "Delete first copy...\n" ;
   delete Tptr ;

   cout << "Recheck original:    " ;
   T1.inorder() ; cout << endl ;
   cout << "Recheck second copy: " ;
   T2.inorder() ; cout << endl ; 
   
}
