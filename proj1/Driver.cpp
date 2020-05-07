/*****************************************
 ** File:    Graph.cpp
 ** Project: CMSC 341 Project 1, Spring 2017
 ** Author:  Aishwarya Panchumarty
 ** Date:    02/16/17
 ** Section: 03
 ** E-mail:  aispan1@umbc.edu
 **
 ** This file contains the implementations
 ** of the functions in Graph.h.
 **
 ***********************************************/
#include <iostream>

// need this for pair template
//
#include <utility>
using namespace std ;

#include "Graph.h"

int main() {
  // G has 5 vertices numbered 0 thru 4
  Graph G(5) ;
  // add some edges
  G.addEdge(3,4) ;
  G.addEdge(1,4) ;
  G.addEdge(0,3) ;
  G.addEdge(0,4) ;

  // dump out data structure
  G.dump() ;

  // Test neighbor iterator
  //
  Graph::NbIterator nit ;

  cout << "\nThe neighbors of vertex 0 are:\n" ;
  for (nit = G.nbBegin(0); nit != G.nbEnd(0) ; nit++) {
    cout << *nit << " " ;
  }
  cout << endl ;


  // Test edge iterator
  //
  Graph::EgIterator eit ;
  pair<int,int> edge ;

  cout << "\nThe edges in the graph are:\n" ;
  for (eit = G.egBegin() ; eit != G.egEnd() ; eit++) {

    edge = *eit ;   // get current edge

    // the two data members of a pair are first and second
    //
    cout << "(" << edge.first << ", " << edge.second << ") " ;

  }
  cout << endl ;

  Graph* Gptr = new Graph(5) ;

  // add some edges
  Gptr->addEdge(3,4) ;
  Gptr->addEdge(1,4) ;
  Gptr->addEdge(0,3) ;
  Gptr->addEdge(0,4) ;
  Gptr->addEdge(0,1) ;
  Gptr->addEdge(1,2) ;
  Gptr->addEdge(2,4) ;

  // dump out data structure
  Gptr->dump() ;

  // make a copy using copy constructor
  Graph* Gptr2 = new Graph(*Gptr) ;
  Gptr2->dump() ;

  // get rid off original graph
  // check if new graph is still there
  delete Gptr ;
  Gptr2->dump() ;

  delete Gptr2;
  try
  Graph exceptionG(-1000);
}
