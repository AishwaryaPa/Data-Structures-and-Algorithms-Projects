// File: test7.cpp
//
// Big test with recursive sanityCheck() and lots of data.
//

#include <iostream>
#include <stdexcept>
using namespace std ;

#include "LazyBST.h"

const int depthLimit = 30 ;


// This function recursively checks if a LazyBST is correct, by checking:
//
//   1. keys are in order
//   2. left subtree is not more than twice the size of right subtree
//      or vice versa
//
// This function relies on locate() member function working correctly.
//
// Parameters:  
//   LazyBST& T  = tree to be checked, passed by reference
//   char pos[]  = must be pre-allocated with depthLimit chars
//   int& key    = stores key in node indicated by pos, if it exists
//   int& height = stores height of node indicated by pos, if it exists
//   int& size   = stores size of node indicated by pos, if it exists
//   bool report = give report for current node? defaults to true.
//
// Return value:
//    true if T has a node at pos
//    false if T does not have a node at pos
//
// Notes: 
// - if return value is false, parameters key, height and size are
//   not changed.
// - The pos string/array essentially acts as a stack for exploration
//   of the LazyBST. It remembers where we've been and is used to
//   determine where we have to check next.
//

bool sanityCheck(LazyBST& T, char pos[], int depth, int& key, int& height, int& size, bool report=true) {

   int leftKey, rightKey ;
   int leftHeight=-1, rightHeight=-1 ;
   int leftSize=0, rightSize=0 ;
   bool hasLeft, hasRight ;


   // Try to catch bad BST with cycles
   //
   if (depth >= depthLimit) {
      throw out_of_range("Depth limit reached. Something looks wrong!\n") ;
   }


   // Is does current position have a node?
   //
   if ( ! T.locate(pos, key) ) return false ;


   // Add extra '\0' so pos string can be extended
   //
   pos[depth+1] = '\0' ;


   // Recursively checks left subtree.
   //
   pos[depth] = 'L' ;
   hasLeft= sanityCheck(T, pos, depth+1, leftKey, leftHeight, leftSize, report) ;


   // Recursively checks right subtree.
   //
   pos[depth] = 'R' ;
   hasRight= sanityCheck(T, pos, depth+1, rightKey, rightHeight, rightSize, report) ;


   pos[depth] = '\0' ;  // restores pos[]


   // Compute current node's height and size
   //
   height = 1 + ( (leftHeight > rightHeight) ? leftHeight : rightHeight ) ; 
   size = 1 + leftSize + rightSize ;


   // Check key ordering for left child
   //
   if (hasLeft && leftKey >= key) {
      cerr << "\nIn position " << pos 
           << " (key=" << key << ",height=" << height << ",size=" << size << ")"
           << " left child's key not less than current node's key:"
	   << leftKey << " " << key << endl ;
   }


   // Check key ordering for right child
   //
   if (hasRight && rightKey <= key) {
      cerr << "\nIn position " << pos 
           << " (key=" << key << ",height=" << height << ",size=" << size << ")"
           << " right child's key not greater than current node's key:"
	   << rightKey << " " << key << endl ;
   }


   // Check relative sizes of left and right subtrees.
   // Note: leftSize == 2* rightSize (or vice versa) is not an error
   //    because it is up to the next insert or remove to fix.
   //
   if (height > 3) {
      if (leftSize > 2 * rightSize) {
	 cerr << "\nIn position " << pos 
              << " (key=" << key << ",height=" << height << ",size=" << size << ")"
	      << " left subtree too big: "
	      << leftSize << " " << rightSize << endl ;
      }
      if (rightSize > 2 * leftSize) {
	 cerr << "\nIn position " << pos 
              << " (key=" << key << ",height=" << height << ",size=" << size << ")"
	      << " right subtree too big: "
	      << leftSize << " " << rightSize << endl ;
      }

   }


   // Give stats for current node, if so desired.
   //

   if (report) {
      cout << "\n Node report on position " << pos << " :" << endl ;
      cout << "   key = " << key 
	   << "   height = " << height 
	   << "   size = " << size 
	   << endl ;

      if (hasLeft) {
	 cout << "   left child key = " << leftKey << endl ;
      } else {
	 cout << "   no left child\n" ;
      }

      if (hasRight) {
	 cout << "   right child key = " << rightKey << endl ;
      } else {
	 cout << "   no right child\n" ;
      }
   }

   return true ;

}






int main() {

   LazyBST T ;

   // add a bunch of numbers
   //
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
   T.insert(38) ;
   T.insert(81) ;
   T.insert(95) ;
   T.insert(43) ;
   T.insert(17) ;

   T.inorder() ; cout << endl ;

   char pos[depthLimit] ;
   pos[0] = '\0' ;
   int key, height, size ;

   // Do check
   //
   cout << "First a small test...\n" ;
   sanityCheck(T,pos,0,key,height,size) ;
   cout << "\n\nSmall tree has root with key=" << key
        << ", height=" << height 
	<< ", size=" << size 
	<< endl; 

   cout << endl << endl ;
   cout << "Now a big test...\n" ;

   LazyBST T2 ;

   for (int i=1000 ; i<1500 ; i++) {
      T2.insert(i) ;
   }
   for (int i=250 ; i<900 ; i++) {
      T2.insert(i) ;
   }
   for (int i=3000 ; i>1600 ; i--) {
      T2.insert(i) ;
   }
   for (int i=3500 ; i<6000 ; i++) {
      T2.insert(i) ;
   }

   sanityCheck(T2,pos,0,key,height,size,false) ;
   cout << "\n\nBig tree has root with key=" << key
        << ", height=" << height 
	<< ", size=" << size 
	<< endl; 

   cout << endl << endl ;

}
