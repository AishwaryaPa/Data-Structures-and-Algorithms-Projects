// File: test6.cpp
//
// Simple test of locate() function
//

#include <iostream>
using namespace std ;

#include "LazyBST.h"

int main() {

   LazyBST T ;

   T.insert(70) ;
   T.insert(30) ;
   T.insert(110) ;
   T.insert(40) ;
   T.insert(20) ;
   T.insert(41) ;
   T.insert(31) ;
   T.insert(32) ;
   T.insert(33) ;
   T.insert(19) ;
   T.insert(34) ;
   T.insert(15) ;
   T.insert(14) ;

   T.inorder() ; cout << endl ;

   int key = 9999 ;
   bool ans ;
   const char *str ;

   ans = T.locate(str="", key=-1) ;
   cout << str << ": " << ans << " " << key << endl ;

   ans = T.locate(str="LL", key=-1) ;
   cout << str << ": " << ans << " " << key << endl ;

   ans = T.locate(str="LLR", key=-1) ;
   cout << str << ": " << ans << " " << key << endl ;

   ans = T.locate(str="RLLR", key=-1) ;
   cout << str << ": " << ans << " " << key << endl ;


}
