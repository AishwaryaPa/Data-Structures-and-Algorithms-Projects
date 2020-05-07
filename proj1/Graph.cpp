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
# include "Graph.h"
# include <iostream>
# include <string>

// Graph(int n)
// Creates an object of Graph. Must be given vertices or
// an exception will be thrown
Graph::Graph(int n){
  if (n <= 0){  
    throw std::out_of_range("Invalid number of vertices to construct Graph.");
  }
  else{
    m_size = n;
    m_adjLists = new AdjListNode*[m_size]; // create the array and populate it with
                                          // first node of every linked list 
    for(int i = 0; i < m_size; i++){
      AdjListNode * next = NULL;
      AdjListNode *newNodePtr = new AdjListNode(i, next);
      m_adjLists[i] = newNodePtr;
    }
  }
}

// Graph(const Graph& G)
// Copy constructor for graph
Graph::Graph(const Graph& G){
  m_size = G.m_size; 
  m_adjLists = new AdjListNode*[G.m_size]; // Dynamically allocate a new array first
                                          // with the same excat size of the original object
  for (int i = 0; i < G.m_size; i++){
    AdjListNode * next = NULL;
    AdjListNode * firstNode = new AdjListNode(G.m_adjLists[i]->m_vertex, next); // populate it with first node of every linked list in original object
    m_adjLists[i] = firstNode;

    AdjListNode * temp = firstNode; // temp is used increment to the next node in the copy object

    AdjListNode * curr = G.m_adjLists[i]; // curr is used to increment to the next node in the original object
    curr = curr->next;
    while(curr != NULL){ // stop when they are no nodes to copy
      AdjListNode * newNode = new AdjListNode(curr->m_vertex, next);
      temp->next = newNode;
      temp = temp->next;
      curr = curr->next;
    }

  }
}

// Graph destructor
// deallocates the dynamically allocated data
Graph::~Graph(){
  // delete every node in the list
  for (int i = 0; i < m_size; i++){ 
    AdjListNode * curr = m_adjLists[i];
    AdjListNode * after = m_adjLists[i];
    while (after != NULL)
      {
	curr = after;
	after = after->next;
	delete curr;
      }
  }

  // finally delete the array itself
  delete [] m_adjLists;
  m_adjLists = NULL;
}

//Graph assignment operator
const Graph& Graph::operator= (const Graph& rhs){
  // delete every node in the list
  if (this!= &rhs){
    for (int i = 0; i < this->m_size; i++){
      AdjListNode * curr = this->m_adjLists[i];
      AdjListNode * after = this->m_adjLists[i];
      while (after != NULL)
	{
	  curr = after;
	  after = after->next;
	  delete curr;
	}
    }
  
    // finally delete the array itself
    delete [] m_adjLists;
    m_adjLists = NULL;

    m_size = rhs.m_size;
    m_adjLists = new AdjListNode*[rhs.m_size]; // Dynamically allocate a new array first
    // with the same excat size of the original object
    for (int i = 0; i < rhs.m_size; i++){
      AdjListNode * next = NULL;
      AdjListNode * firstNode = new AdjListNode(rhs.m_adjLists[i]->m_vertex, next); // populate it with first node of every linked list in original object
      m_adjLists[i] = firstNode;

      AdjListNode * temp = firstNode; // temp is used increment to the next node in the copy object

      AdjListNode * curr = rhs.m_adjLists[i]; // curr is used to increment to the next node in the original object
      curr = curr->next;
      while(curr != NULL){ // stop when they are no nodes to copy
	AdjListNode * newNode = new AdjListNode(curr->m_vertex, next);
	temp->next = newNode;
	temp = temp->next;
	curr = curr->next;
      }

    }
    
  }
  return *this;
}

// size()
// return number of vertices
int Graph::size(){
  return m_size;
}

// addEdge()
// Adds an edge between u and v. If the values for u and v 
// are out of bounds, throw an out_of_range exception. Has 
// to update the graph twice because u is neighbo of v
// and v is a neighbor of u
// *********************** add at the begining of the linked list not at the end ********************
void Graph::addEdge(int u, int v){ 
  // if incorrect values were given
  if(u < 0 or u > m_size or v < 0 or v > m_size){
    throw std::out_of_range("Incorrect values to add an edge");
  }
  
  // otherwise add the edge using both vertices even though this will create duplicates
  else{
    AdjListNode *curr = m_adjLists[u];
    AdjListNode * temp = m_adjLists[u]->next;
    
    AdjListNode * nextAddress = NULL;
    AdjListNode *newNodePtr = new AdjListNode(v, nextAddress);
    
    curr->next = newNodePtr;
    newNodePtr->next = temp;

    AdjListNode *curr2 = m_adjLists[v];
    AdjListNode * temp2 = m_adjLists[v]->next;

    AdjListNode * nextAddress2 = NULL;
    AdjListNode *newNodePtr2 = new AdjListNode(u, nextAddress2);

    curr2->next = newNodePtr2;
    newNodePtr2->next = temp2;
  }
}

// dump()
// print out data structure for debugging 
// without using the iterators
void Graph::dump(){
  std::cout <<"Dump out graph (size = " << m_size << ")" << std::endl;
  for (int i = 0; i < m_size; i++){ // set curr to the one next to it
    std::cout << "[" << i << "]: ";
    AdjListNode *curr;
    for(curr = m_adjLists[i]->next; curr != NULL; curr = curr->next){
      std::cout << curr->m_vertex << " ";
    }
    std::cout << std::endl;
  }
}

// EgIterator(Graph *Gptr, bool isEnd)
// Edge Iterator constructor. Creates an object of iterators
// depending on the parameters. If isEnd is equal to true,
// then create an end iterator. If it is false, then create
// an begin iterator. If proper requirements were not met
// then create an object using default values
Graph::EgIterator::EgIterator(Graph *Gptr, bool isEnd){
 m_Gptr = Gptr;    // pointer to Graph using this iterator
 
 // create the end iterator
 if (isEnd == true and  m_Gptr != NULL){
   m_source = m_Gptr->m_size;          // source vertex of current location
   m_where = NULL;  // location in linked list of iterator
  }

 // create the begining iterator
  else if (isEnd == false and m_Gptr != NULL){
    m_source = 0;          // source vertex of current location
    m_where = m_Gptr->m_adjLists[0]->next;  // location in linked list of iterator
  }

 // create an iterator that is neither the begining or end
 // this iterator will be created if the requirements above were not met
  else if (isEnd == false and m_Gptr == NULL){ // object created without any parameters
    m_source = -1;
    m_where = NULL;
  }
}

// operator!= (const EgIterator& rhs)
// Compare edge iterators to check if end has been reached
bool Graph::EgIterator::operator!= (const EgIterator& rhs){
  if (m_where != NULL and m_source != ((m_Gptr->m_size) - 1)){ 
    return true;
  }
  else{
    return false; // stop when the last value has been reached
  }
  
}

// operator++(int dummy)
// Move iterator to next printable edge. There are duplicates 
// edges in the list. (3, 4) and (4, 3) are the same edge,
// so while incrementing, check if the current edge is  duplicate
// or not
void Graph::EgIterator::operator++(int dummy){
  bool stop = false;
  while(stop != true){
    if (m_where->next == NULL and m_source == ((m_Gptr->m_size) - 1)){ // don't increment if this is the last node in the entire list
      stop = true;
    }
    else if(m_where->next == NULL and m_source < ((m_Gptr->m_size) - 1)){ // increment to the first node in the next linked list if 
      m_source = m_source + 1;                                           // the iterator reached the end of a linked other than the last one
      m_where = m_Gptr->m_adjLists[m_source];
      if (m_where->m_vertex > m_source){
        stop = true;
      }
    }
    else if(m_where->next != NULL and m_source <= ((m_Gptr->m_size) - 1)){
      m_where = m_where->next;
      if (m_where->m_vertex > m_source){
	stop = true;
      }
    }
  } 
  
}

// operator*()
// Return edge at iterator location in the form of a pair. 
std::pair<int,int> Graph::EgIterator::operator*(){
  if (m_where == NULL){
    throw std::out_of_range("EgIterator dereference error.");
  }
  else{
    std::pair<int, int> edge(m_source, m_where->m_vertex);
    return edge;
  } 
}

// egBegin()
// Make an initial edge Iterator
Graph::EgIterator Graph::egBegin(){
  EgIterator begin = EgIterator(this, false);
  return begin;  
}

// egEnd()
// Make an end iterator for edge iterator
Graph::EgIterator Graph::egEnd(){
  EgIterator end = EgIterator(this, true);
  return end;

}
// NbIterator(Graph *Gptr, int v, bool isEnd)
// Constructor for neightbor iterator for vertices adjacent 
// to vertex v. This iterator only moves through one linked 
// list at a time. If isEnd is equal to true,
// then create an end iterator. If it is false, then create
// an begin iterator. If proper requirements were not met
// then create an object using default values
Graph::NbIterator::NbIterator(Graph *Gptr, int v, bool isEnd){
  m_Gptr = Gptr;          // which graph?
  m_source = v;   // neighbor of which vertex?
  
  if (Gptr != NULL and v >= 0){
    if (isEnd == true){
      m_where = NULL;
    }
    else if (isEnd == false){
      m_where = m_Gptr->m_adjLists[m_source]->next;   // location in linked list
    }
  }
}

// operator!= (const NbIterator& rhs)
// Compare two neighbor iterators and checks if end has been reached.
bool Graph::NbIterator::operator!= (const NbIterator& rhs){
  if (m_where != rhs.m_where){
    return true;
  }
  else{
    return false;
  }
}

// operator++(int dummy)
// Move iterator to next neighbor if it exits. 
void Graph::NbIterator::operator++(int dummy){
  if (m_where != NULL){
    m_where = m_where->next;
  }
}

// Operator*()
// Return the current position of the iterator. Make sure 
// the iterator is pointing to NULL
int Graph::NbIterator::operator*(){
  if (m_where == NULL) {
    throw std::out_of_range("NbIterator dereference error.");
  }
  else{
    return m_where->m_vertex;
  }
}

// nbBegin(int v)
// Makes an begining iterator
Graph::NbIterator Graph::nbBegin(int v){
  NbIterator begin = NbIterator(this, v, false);
  return begin;
}

// nbEnd(int v)
// Make an end neighbor iterator
Graph::NbIterator Graph::nbEnd(int v){
  NbIterator end = NbIterator(this, v, true);
  return end;
}
// AdjListNode(int v, AdjListNode *ptr)
// Creates nodes for each linked list in the array
Graph::AdjListNode::AdjListNode(int v, AdjListNode *ptr){
  m_vertex = v;        // holds one neighbor vertex
  next = ptr;  // next node
}


