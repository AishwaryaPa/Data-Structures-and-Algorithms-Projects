// File: nested.cpp
//
// CMSC 341 Spring 2017
//
// All-in-one file showing nested classes and access
//

#include <iostream>
using namespace std ;

class Outer {

public:

   Outer() ; 

   class Inner {

      // Friend declaration necessary for Outer member 
      // functions to access Inner private member 
      // functions and Inner private data members
      //
      friend class Outer ;  

      public:
	 Inner() ;
	 void iFunction() ;
	 void iFunction2(Outer &outerObject) ;

      private:
         int iData ;
   } ;

   void oFunction() ;
   void oFunction2(Inner &innerObject) ;

private:

   int oData ;
   Inner iThing ;

} ;


// Outer constructor
Outer::Outer() {
   oData = 43 ;
}


// "Normal" Outer member function
void Outer::oFunction() {
   cout << "oData = " << oData << endl ;
}


// Outer member function tries to access
// Inner private data member (needs friend declaration)
//
void Outer::oFunction2(Inner &innerObject) {
   cout << "oData = " << oData << endl ;
   cout << "iData = " << innerObject.iData << endl ;
}

// Inner constructor
Outer::Inner::Inner() {
   iData = 72 ;
}

// "Normal" Inner member function
void Outer::Inner::iFunction() {
   cout << "iData = " << iData << endl ;
}

// Inner member function tries to access
// Outer private data member (does not need friend declaration)
//
void Outer::Inner::iFunction2(Outer &outerObject) {
   cout << "oData = " << outerObject.oData << endl ;
   cout << "iData = " << iData << endl ;
}


// Testing with main()
//
int main() {
   
   // Note: don't need Outer object to define an Inner object
   Outer::Inner y ;  

   Outer x ; 

   cout << "Calling Outer functions:\n" ;
   x.oFunction() ;
   x.oFunction2(y) ;

   cout << "Calling Inner functions:\n" ;
   y.iFunction() ;
   y.iFunction2(x) ;

   return 0 ;
}
