// File: test2.cpp
//
// CMSC 341 Spring 2017
// Project 1 
//
// Testing of Graph destructor, copy constructor and assignment operator
//

#include <iostream>

// need this for pair template
//
#include <utility>
using namespace std ;

#include "Graph.h"

int main() {

   Graph* Gptr = new Graph(5) ;

   // add some edges
   Gptr->addEdge(3,4) ;
   /*   Gptr->addEdge(1,4) ;
   Gptr->addEdge(0,3) ;
   Gptr->addEdge(0,4) ;
   Gptr->addEdge(0,1) ;
   Gptr->addEdge(1,2) ;
   Gptr->addEdge(2,4) ;
   Gptr->addEdge(2,2) ;*/

   // dump out data structure
   Gptr->dump() ;

   // make a copy using copy constructor
   Graph* Gptr2 = new Graph(*Gptr) ;
   Gptr2->dump() ;

   // get rid off original graph
   // check if new graph is still there
   delete Gptr ;
   Gptr2->dump() ;

   // Make another graph and dump
   Graph G3(3) ;
   G3.addEdge(0,1) ;
   G3.addEdge(0,2) ;
   G3.addEdge(1,2) ;
   G3.dump() ;

   // Copy over G3 and dump
   G3 = *Gptr2 ;
   G3.dump() ; 

   delete Gptr2 ; 
}
