/*****************************************
 ** File:    MinMaxHeap.h
 ** Project: CMSC 341 Project 4, Spring 2017
 ** Author:  Aishwarya Panchumarty
 ** Date:    04/21/17
 ** Section: 03
 ** E-mail:  aispan1@umbc.edu
 **
 ** This file contains the class declarations
 ** for MinMaxHeap class
 ** 
 ***********************************************/

#ifndef MINMAXHEAP_H
#define MINMAXHEAP_H

#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

template <typename T>
class Heap{
 public:
  int m_capacity; // Keeps track of how big the array can get
  int m_size; // Keeps track of the Array's current size
  bool (*m_funcPtr)(T, T); // function pointer
  //  Node * m_arrayNodes; // Array storing all the nodes in order

  Heap<T> *m_other;

  // Name: Constructor for Heap class
  // PreCondition: None
  // PostCondition: Creates a Heap object
  Heap();

  // Name: Destructor for Heap class
  // PreCondition: None
  // PostCondition: Deallocates all the memory
  ~Heap();

  // Name: GetSize(); 
  // PreCondition: None
  // PostCondition: Returns the size
  int GetSize();

  // Name: SetUpArray()
  // PreCondition: None
  // PostCondition: Dynamically allocates space for the array
  void SetUpArray(int capacity);

  // Name: InsertNode(T data);
  // PreCondition: Array must be allocated
  // PostCondition: inserts a node into the array
  void InsertNode(T data);

  // Name: BubbleUp
  // PreCondition: Array must be allocated
  // PostCondition: Repairs the heap if it becomes unorganized
  void BubbleUp(int position);

  // Name: UpdataTwin(T data, int index);
  // PreCondition: The node to be updated must already exist
  // PostCondition: Updates the newly inserted node in the array with its twin 
  void UpdateTwin(T data, int twinIndex);

  // Name: GetIndex(T data);
  // PreCondition: The data must exist in the array
  // PostCondition: returns the index of where a certain value is stored
  int GetIndex(T data);

  // Name: ValidateIndex();
  // PreCondition: Array must be allocated
  // PostCondition: Checks if the children exist
  bool ValidateIndex(int index);

  // Name: DeleteTop()
  // PreCondition: Array must be allocated
  // PostCondition: Deletes the first value in the array
  T DeleteTop();

  // Name: TrickleDown()
  // PreCondition: Array must be allocated
  // PostCondition: Repairs the heap
  void TrickleDown(int position);

  // Name: DeleteValue()
  // PreCondition: Other heap must exist
  // PostCondition: Deletes the twin in other heap
  void DeleteValue(int index);

  // Name: Swap(int position1, int position2)
  // PreCondition: Array must be allocated
  // PostCondition: Swaps the data of the given indices
  void Swap(int position1, int position2);  

  // Name: Print();
  // PreCondition: The array must be filled with data
  // PostCondition: Prints all the data
  void Print();

  // Name: GetData()
  // PreCondition: The array must be filled with data
  // PostCondition: Fetches the data in the given position
  T GetData(int position);

  // Name: GetTwin()
  // PreCondition: The array must be filled with data
  // PostCondition: Fetches the data in the given position
  int GetTwin(int position);

 private:
  class Node {
    friend class Heap;
  public:
    // Name: Constructor for Binary Node
    // PreCondition: Must be called by public functions only
    // PostCondition: Creates a node
    Node();
    //    Node(const Node<T>& other);

    T m_data; // Data in the node
              // must be templated so it can accept any type of data

    int m_twinIndex; // Must keep track of where its twin is located in the other heap

  };

  Node * m_arrayNodes; // Array storing all the nodes in order

};




template <typename T>
class MinMaxHeap{
 public:
  // Name: Constructor for MinMaxHeap()
  // PreCondition: None
  // PostCondition: creates an object of MinMaxHeap
  MinMaxHeap(int capacity)  ;

  // Name: Copy Constructor
  // PreCondition: The other object must exist
  // PostCondition: Creates a deep copy
  MinMaxHeap(const MinMaxHeap<T>& other)  ;

  // Name: Destructor
  // PreCondition: None
  // PostCondition: None
  ~MinMaxHeap()  ;

  // Name: Assignment Operator
  // PreCondition: The rhs object must exist
  // PostCondition: Sets the current object equal to the old object
  const MinMaxHeap<T>& operator=(const MinMaxHeap<T>& rhs)  ;

  // Name: size()
  // PreCondition: None
  // PostCondition: Gets the size of the min heap
  int size() ;

  // Name: insert()
  // PreCondition: Array must be created
  // PostCondition: Inserts data into the array
  void insert(const T& data) ;

  // Name: deleteMin()
  // PreCondition: Array must exist
  // PostCondition: Deletes the minimum in both heaps
  T deleteMin() ;

  // Name: deleteMax()
  // PreCondition: Array must exist
  // PostCondition: Deletes the max in both heaps
  T deleteMax() ;

  // Name: dump()
  // PreCondition: None
  // PostCondition: Prints the heap
  void dump() ;

  // Name: locateMin(int pos, T& data, int& index)
  // PreCondition: Array must exist
  // PostCondition: Returns the data and twin index of the given position in the array
  void locateMin(int pos, T& data, int& index) ;

  // Name: locateMin(int pos, T& data, int& index)
  // PreCondition: Array must exist
  // PostCondition: Returns the data and twin index of the given position in the array
  void locateMax(int pos, T& data, int& index) ;
  
 private:
  Heap<T> m_minHeap;
  Heap<T> m_maxHeap;

};

// Name: maxx()
// PreCondition: Two values must be given
// PostCondition: Returns true if the first value is greater than the second one
template <typename T>  
bool maxx(T a, T b);

// Name: minn()
// PreCondition:  Two values must be given
// PostCondition: Returns true if the first value is greater than the second one
template <typename T>  
bool minn(T a, T b);


//----------------------------------------------------
// Heap()
// Constructor for Heap class
// Creates an object of Heap
template <typename T>
Heap<T>::Heap(){
 
}

// ~Heap()
// Destructor for heap
// Dealllocates the memory for array
template <typename T>
Heap<T>::~Heap(){
  m_funcPtr = NULL;
  delete [] m_arrayNodes;
}

// GetSize()
// Returns the size of the heap
template<typename T>
int Heap<T>::GetSize(){
  return m_size;
}


// InsertNode()
// Adds a node into the array. This function
// should be called by insert in MinMaxHeap class
template <typename T>
void Heap<T>::InsertNode(T data){
  if (m_size == m_capacity){ // reached the capacity
    throw std::out_of_range("Heap is full. Cannot add more data");
  }

  // create the node
  Node value;
  value.m_data = data;
  value.m_twinIndex = -1;

  int position = m_size + 1;

  // insert the node
  m_arrayNodes[position] = value;
  m_size = m_size + 1;
  if (m_size > 1){
    BubbleUp(position); // repair the heap
  }

}

// BubbleUp(int position);
// Repairs the heap by swaping the child and parents until the heap is balanced
template <typename T>
void Heap<T>::BubbleUp(int position){
  int index = position;
  T firstVal = m_arrayNodes[index].m_data; // child value
  T secondVal = m_arrayNodes[index/2].m_data; // parent value

  while(index > 1 && m_funcPtr(firstVal, secondVal)){
    Swap(index, index/2);
    index = index /2; // check the values above
    firstVal = m_arrayNodes[index].m_data; // set the values up for the next loop
    secondVal = m_arrayNodes[index/2].m_data;
   
  }
}


// UpdateTwin()
// updates the newly inserted node with its twin
template <typename T>
void Heap<T>::UpdateTwin(T data, int twinIndex){
  if (m_size >= 1){
    int index = GetIndex(data);
    m_arrayNodes[index].m_twinIndex = twinIndex;
  }
  else{
    throw std::out_of_range("Heap is empty");
  }

}

// SetUpArray()
// Creates a dynamically allocated array
template <typename T>
void Heap<T>::SetUpArray(int capacity){
  m_arrayNodes = new Node[capacity + 1];
}

// GetIndex()
// gets the index of where a certain value
// is inserted in the array
template <typename T>
int Heap<T>::GetIndex(T data){
  unsigned int index = -1;

  for (unsigned int i = 1; i <= m_size; i++){
    if (m_arrayNodes[i].m_data == data){
      index = i;
    }
  }
  
  if (index == -1){
    throw std::out_of_range("The given data does not exist in Heap");
  }
   return index;
}

// ValidateIndex(int index);
// Checks if the index is valid
template <typename T>
bool Heap<T>::ValidateIndex(int index){
  if (index == 0 or index > m_size){
    return false;
  }
  
  return true;
  
}

// Delete Top
// Deletes the first value in the heap
template <typename T>
T Heap<T>::DeleteTop(){
  if (m_size == 0){
    throw std::out_of_range("Heap is Empty. Cannot delete a value");
  }

  T data = m_arrayNodes[1].m_data;
  int twinIndex = m_arrayNodes[1].m_twinIndex;
  
  // delete the first value
  int index = 1;
  Swap(index, m_size);
  m_size = m_size - 1;
  TrickleDown(index);
  
  // delete the twin value
  DeleteValue(twinIndex);
  return data;
}

// TrickleDown()
// Repairs the heap by swaping downwards with parent and child
template <typename T>
void Heap<T>::TrickleDown(int position){
  int index = position;
  int leftChild = 2 * index;
  int rightChild = (2 * index) + 1;

  while(index >= 1 and index < m_size){
    if (ValidateIndex(leftChild) == true and ValidateIndex(rightChild) == true){ // if both children exist

      T leftData = m_arrayNodes[2 * index].m_data;
      T rightData = m_arrayNodes[2 * index + 1].m_data;

      // check which child is smaller or biggest
      if (m_funcPtr(leftData, rightData)){ // if the left child is smaller or bigger
        Swap(index, leftChild);
	index = leftChild;
      }

      else{ // if the right child is smaller
        Swap(index, rightChild);
	index = rightChild;
      }
    }

    else if (ValidateIndex(leftChild) == true and ValidateIndex(rightChild) == false){ // if only the left child exists
      T leftData = m_arrayNodes[2 * index].m_data;

      // check if the current index or the left child is smaller
      if (m_funcPtr(leftData, m_arrayNodes[index].m_data)){  // if the left child is smaller or bigger, then swap otherwise
        Swap(leftChild, index);  // don't do anything
	index = leftChild;
      }
      
      else{
	index = m_size;
      }

    }
    else{ // No children 
      index = m_size;
    }

    //index = index * 2; // set up the values for the next loop
    leftChild = 2 * index;
    rightChild = (2 * index) + 1;

  }
}

// DeleteValue()
// Deletes the twin node in the other heap
template <typename T>
void Heap<T>::DeleteValue(int index){
  // swap the value to be deleted with the last node in the other heap
  m_other->Swap(index, m_other->m_size);
  m_other->m_size = m_other->m_size - 1;
  int leftChild = 2 * index;
  int rightChild = (2 * index) + 1;
  
  // check if the new node has children
  // if no children
  if (m_other->ValidateIndex(leftChild) == false and m_other->ValidateIndex(rightChild) == false){
    m_other->BubbleUp(index); // then bubble up to repair the heap
  } 

  // if it does have children
  else{
    // check how many
    // only one child
    if (m_other->ValidateIndex(leftChild) == true and m_other->ValidateIndex(rightChild) == false){
      T firstVal = m_other->m_arrayNodes[index].m_data;
      T secondVal = m_other->m_arrayNodes[index * 2].m_data;
 
      if(m_other->m_funcPtr(firstVal, secondVal)){
	m_other->BubbleUp(index);
      }

      else{
	m_other->TrickleDown(index);
      }
    }
    
    // two children
    else if (m_other->ValidateIndex(leftChild) == true and m_other->ValidateIndex(rightChild) == true){
      T firstVal = m_other->m_arrayNodes[index].m_data;
      T secondVal = m_other->m_arrayNodes[index * 2].m_data;
      T thirdVal = m_other->m_arrayNodes[(index * 2) + 1].m_data;

      if(m_other->m_funcPtr(firstVal, secondVal) == true  and m_other->m_funcPtr(firstVal, thirdVal) == true){
        m_other->BubbleUp(index);
      }

      else{
        m_other->TrickleDown(index);
      }
    }
  }
}

// Swap(int position1, int position2)
// Swaps the values in position1 and position2
template <typename T>
void Heap<T>::Swap(int position1, int position2){
  T data = m_arrayNodes[position1].m_data;              // store the values temporarily of the data to be swapped
  int twinIndex = m_arrayNodes[position1].m_twinIndex;

  m_arrayNodes[position1].m_data = m_arrayNodes[position2].m_data; // swap parent and child
  m_arrayNodes[position1].m_twinIndex = m_arrayNodes[position2].m_twinIndex;

  int swapedValueIndex = m_arrayNodes[position1].m_twinIndex;

  if (swapedValueIndex != -1){ // -1 is only assigned to values that don't yet exist in the other heap
    m_other->m_arrayNodes[swapedValueIndex].m_twinIndex = position1; // update the twin value in other heap if the value exists
  }

  m_arrayNodes[position2].m_data = data;
  m_arrayNodes[position2].m_twinIndex = twinIndex;

  int swapedValueIndex2 = m_arrayNodes[position2].m_twinIndex;

  if (swapedValueIndex2 != -1){
    m_other->m_arrayNodes[swapedValueIndex2].m_twinIndex = position2;
  }
}

// Print()
// Prints the heap
template <typename T>
void Heap<T>::Print(){
  cout << "size = " << m_size << ", capacity = " << m_capacity << endl;

  for(int i = 1; i <= m_size; i++){
    cout <<"Heap[" << i << "] = (" << m_arrayNodes[i].m_data << "," << m_arrayNodes[i].m_twinIndex << ")" << endl;
  }
}

// GetData()
// Gets the data from a certain position
template <typename T>
T Heap<T>::GetData(int position){
  return m_arrayNodes[position].m_data;
}

// GetTwin()
// Gets the data from a certain position 
template <typename T>
int Heap<T>::GetTwin(int position){
  return m_arrayNodes[position].m_twinIndex;
}


// Node()
// Constructor for the node class
template <typename T>
Heap<T>::Node::Node(){

}

// MinMaxHeap(int capacity)
// Constructor for the MinMaxHeap class
template <typename T>
MinMaxHeap<T>::MinMaxHeap(int capacity){
  m_minHeap.m_capacity = capacity;
  m_minHeap.m_size = 0;
  m_minHeap.m_funcPtr = &minn;
  m_minHeap.SetUpArray(capacity);

  m_maxHeap.m_capacity = capacity;
  m_maxHeap.m_size = 0;
  m_maxHeap.m_funcPtr = &maxx;
  m_maxHeap.SetUpArray(capacity);

  m_minHeap.m_other = &m_maxHeap;
  m_maxHeap.m_other = &m_minHeap;
  
}

// Copy Constructor
// Creates a deep copy of the MinMaxHeap object
template <typename T>
MinMaxHeap<T>::MinMaxHeap(const MinMaxHeap<T>& other){
  m_minHeap.m_capacity = *other.capacity;
  m_minHeap.m_size = 0;
  m_minHeap.m_funcPtr = &minn;
  m_minHeap.SetUpArray(*other.capacity);

  m_maxHeap.m_capacity = *other.capacity;
  m_maxHeap.m_size = 0;
  m_maxHeap.m_funcPtr = &maxx;
  m_maxHeap.SetUpArray(*other.capacity);

  m_minHeap.m_other = &m_maxHeap;
  m_maxHeap.m_other = &m_minHeap;
}

// Destructor
template <typename T>
MinMaxHeap<T>::~MinMaxHeap(){

}

// Assignment operator
template <typename T>
const MinMaxHeap<T> &MinMaxHeap<T>::operator=(const MinMaxHeap<T>& rhs){
  m_minHeap.~Heap();
  m_maxHeap.~Heap();

  *m_minHeap.m_capacity = *rhs.capacity;
  *m_minHeap.m_size = 0;
  *m_minHeap.m_funcPtr = &minn;
  *m_minHeap.SetUpArray(*rhs.capacity);

  *m_maxHeap.m_capacity = *rhs.capacity;
  *m_maxHeap.m_size = 0;
  *m_maxHeap.m_funcPtr = &maxx;
  *m_maxHeap.SetUpArray(*rhs.capacity);

  *m_minHeap.m_other = &m_maxHeap;
  *m_maxHeap.m_other = &m_minHeap;

  return *this;
}

// size()
template <typename T>
int MinMaxHeap<T>::size(){
  return m_minHeap.m_size;
}

// insert()
template <typename T>
void MinMaxHeap<T>::insert(const T& data){
  // insert in both heaps first
  m_minHeap.InsertNode(data);
  m_maxHeap.InsertNode(data);
  
  // Get the positions of where the nodes were placed in heap
  int minNodePos = m_minHeap.GetIndex(data);
  int maxNodePos = m_maxHeap.GetIndex(data);
  
  // Update the twin index
  m_minHeap.UpdateTwin(data, maxNodePos);
  m_maxHeap.UpdateTwin(data, minNodePos); 
  
}

// deleteMin()
template <typename T>
T MinMaxHeap<T>::deleteMin(){
  T data =   m_minHeap.DeleteTop();
  return data;
}

// deleteMax()
template <typename T>
T MinMaxHeap<T>::deleteMax(){
  T data = m_maxHeap.DeleteTop();
  return data;
}

// dump()
template <typename T>
void MinMaxHeap<T>::dump(){ 
  cout <<  "... MinMaxHeap::dump() ..." << endl;
  cout << " " << endl;
  cout <<"------------Min Heap------------" << endl;
  m_minHeap.Print();
  cout << " " << endl;
  cout << "------------Max Heap------------" << endl;
  m_maxHeap.Print();
  cout << " " << endl;
}

// locateMin()
template <typename T>
void MinMaxHeap<T>::locateMin(int pos, T& data, int& index){
  data = m_minHeap.GetData(pos);
  index = m_minHeap.GetTwin(pos);
}

// locateMax()
template <typename T>
void MinMaxHeap<T>::locateMax(int pos, T& data, int& index){
  data = m_maxHeap.GetData(pos);
  index = m_maxHeap.GetTwin(pos);
}

// bool maxx(T a, T b)
// stand alone templated function used by max heap
template <typename T>
bool maxx(T a, T b){
  return (a >= b) ? true : false;
}

// bool minn(T a, T b)
// stand alone templated function used by min heap
template <typename T>
bool minn(T a, T b){
  return (a <= b) ? true : false;
}

#endif


