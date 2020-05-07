// File: test8.cpp
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

  T.insert(80) ;
  T.inorder() ; cout << endl ;

  T.insert(20) ;
  T.inorder() ; cout << endl ;

  T.insert(40) ;
  T.inorder() ; cout << endl ;

  T.insert(90) ;
  T.inorder() ; cout << endl ;

  T.insert(75) ;
  T.inorder() ; cout << endl ;

  T.insert(15) ;
  T.inorder() ; cout << endl ;

  T.insert(22) ;
  T.inorder() ; cout << endl ;

  T.insert(10) ;
  T.inorder() ; cout << endl ;

  T.insert(8) ;
  T.inorder() ; cout << endl ;


  return 0;
}
