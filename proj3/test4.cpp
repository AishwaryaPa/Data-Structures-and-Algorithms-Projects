// File: test4.cpp
//
// Checking return values from remove and find.
//

#include <iostream>
using namespace std ;

#include "LazyBST.h"

int main() {

   LazyBST T ;

   T.insert(14) ;

   T.insert(7) ;
   T.insert(3) ; T.insert(1) ; T.insert(4) ;
   T.insert(10) ; T.insert(9) ; T.insert(12) ;

   T.insert(25) ;
   T.insert(18) ; T.insert(15) ; T.insert(21) ;
   T.insert(32) ; T.insert(29) ; T.insert(44) ;

//   T.dump() ;
   T.inorder() ; cout << endl ;

   int n, answer ;


   n = 3  ;
   cout << "Find " << n << endl ;
   if ( T.find(n) ) { 
      cout << "found = " << n << endl ;
   } else {
      cout << "did not find = " << n << endl ;
   }
   cout << endl ;


   n = 4  ;
   cout << "Find " << n << endl ;
   if ( T.find(n) ) { 
      cout << "found = " << n << endl ;
   } else {
      cout << "did not find = " << n << endl ;
   }
   cout << endl ;


   n = 29  ;
   cout << "Find " << n << endl ;
   if ( T.find(n) ) { 
      cout << "found = " << n << endl ;
   } else {
      cout << "did not find = " << n << endl ;
   }
   cout << endl ;


   n = 39  ;
   cout << "Find " << n << endl ;
   if ( T.find(n) ) { 
      cout << "found = " << n << endl ;
   } else {
      cout << "did not find = " << n << endl ;
   }
   cout << endl ;


   n = 301  ;
   cout << "Find " << n << endl ;
   if ( T.find(n) ) { 
      cout << "found = " << n << endl ;
   } else {
      cout << "did not find = " << n << endl ;
   }
   cout << endl ;


// Checking remove...

   n = 21  ;
   cout << "Remove " << n << endl ;
   if ( T.remove(n) ) { 
      cout << n << " removed\n" ;
   } else {
      cout << n << " not found\n" ;
   }
   T.inorder() ; cout << endl ;

   n = 18  ;
   cout << "Remove " << n << endl ;
   if ( T.remove(n) ) { 
      cout << n << " removed\n" ;
   } else {
      cout << n << " not found\n" ;
   }
   T.inorder() ; cout << endl ;

   n = 7  ;
   cout << "Remove " << n << endl ;
   if ( T.remove(n) ) { 
      cout << n << " removed\n" ;
   } else {
      cout << n << " not found\n" ;
   }
   T.inorder() ; cout << endl ;

   n = 13  ;
   cout << "Remove " << n << endl ;
   if ( T.remove(n) ) { 
      cout << n << " removed\n" ;
   } else {
      cout << n << " not found\n" ;
   }
   T.inorder() ; cout << endl ;

   n = 29  ;
   cout << "Remove " << n << endl ;
   if ( T.remove(n) ) { 
      cout << n << " removed\n" ;
   } else {
      cout << n << " not found\n" ;
   }
   T.inorder() ; cout << endl ;

   n = 32  ;
   cout << "Remove " << n << endl ;
   if ( T.remove(n) ) { 
      cout << n << " removed\n" ;
   } else {
      cout << n << " not found\n" ;
   }
   T.inorder() ; cout << endl ;

   n = 14  ;
   cout << "Remove " << n << endl ;
   if ( T.remove(n) ) { 
      cout << n << " removed\n" ;
   } else {
      cout << n << " not found\n" ;
   }
   T.inorder() ; cout << endl ;

}
