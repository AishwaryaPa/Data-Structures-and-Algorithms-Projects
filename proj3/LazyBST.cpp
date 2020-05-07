// /*****************************************
//  ** File:    LazyBST.cpp
//  ** Project: CMSC 341 Project 3, Spring 2017
//  ** Author:  Aishwarya Panchumarty
//  ** Date:    04/09/17
//  ** Section: 03
//  ** E-mail:  aispan1@umbc.edu
//  **
//  ** This file contains the implementations
//  ** for Lazy Binary Tree and its subclass
//  ** BinaryNode
//  ***********************************************/

#include "LazyBST.h"

// LazyBST()
// Constructor for Lazy Binary Tree
// Sets m_root ready for insert()
LazyBST::LazyBST(){m_root = NULL;}


// LazyBST(const LazyBST& other)
// Copy Constructor for Lazy Binary Tree
// Creates a deep copy of the object 
// being called on
LazyBST::LazyBST(const LazyBST &other){
  m_root = copy(other.m_root);
}

// ~LazyBST()
// Destructor for Lazy Binary Tree
// Deallocates all the dynamically allocated
// nodes
LazyBST::~LazyBST() {
  if (m_root != NULL){
    Empty(m_root);
  }
}

// operator=(const LazyBST& rhs) 
// Assignment Operator for Lazy Binary Tree
// Sets the object being called on to 
// another object that already exists
const LazyBST& LazyBST::operator=(const LazyBST& rhs){
  if(this != &rhs){
    Empty(m_root);
    m_root = copy(rhs.m_root);
  }
  return *this;
}

// insert (int key)
// Public version of insert. The user has
// access to this function only. Calls the
// private version of this function
void LazyBST::insert (int key) {
  rebalance1(m_root);
  insert(key, m_root);
}

// remove(int key)
// Public version of remove(). The user has
// access to this function only. Calls the
// private version of this function if the
// given key exists
bool LazyBST::remove(int key) {
  if (find(key, m_root) == true){ // check if key exists
    rebalance1(m_root);
    remove(key, m_root);
    return true;
  }

  else{
    return false;
  }
}

// find(int key)
// Public version of find(). The user has
// access to this function only. Calls the
// private version of this function.
// Returns true if node exists otherwise false
bool LazyBST::find(int key) {
  bool nodeExists = (find(key, m_root));
  if (nodeExists == true){
     return true;
   }
   else{
     return false;
   }
}


// inorder()
// Public version of inorder(). The user has
// access to this function only. Calls the
// private version of this function.
void LazyBST::inorder() {
  inorder(m_root);
}

bool LazyBST::locate(const char *position, int& key){
  int index = 0;
  return locate(position, key, index, m_root);
}

// Private Functions
LazyBST::BinaryNode* LazyBST::copy(const BinaryNode *other){
  if (other == NULL){
    return NULL;
  }

  else{
    BinaryNode *newNode = new BinaryNode(other->m_data, NULL, NULL);

    newNode->m_size = other->m_size;
    newNode->m_height = other->m_height;

    newNode->m_left = copy(other->m_left);
    newNode->m_right = copy(other->m_right);

    return newNode;
  }
}

bool LazyBST::locate(const char *position, int& key, int index, BinaryNode *&root){
  if (root == NULL){
    return false;
  }

  else if (position[index] == '\0'){
    return false;
  }

  else if (position[index] == 'L'){
    index++;
    return locate(position, key, index, root->m_left);
  }

  else if (position[index] == 'R'){
    index++;
    return locate(position, key, index, root->m_right);
  }

}
// insert(int key, BinaryNode * root)
// Private version of insert function.
// Inserts the key where appropriate
// and does nothing if the given key
// already exists
void LazyBST::insert(int key, BinaryNode *& root) {
   
  // first node or reached a place where no data exists
  if (root == NULL){
    root = new BinaryNode(key, NULL, NULL);
  }
  
  // if the key is less than the root, go left
  else if(root->m_data > key){
    insert(key, root->m_left);
  }
  
  // otherwise go right
  else if (root->m_data < key){
    insert(key, root->m_right);
  }

  else if (root->m_data == key){}

  root->m_height = findHeight(root);
  root->m_size = findSize(root);
}

// remove(int key, BinaryNode * root) 
// Private version of remove function
// Removes the key if it exists
bool LazyBST::remove(int key, BinaryNode *& root) {
  if(root == NULL ) { 
    return false; 
  } 
  
  // find the node
  if(root->m_data > key) { 
    remove( key, root->m_left ); 
  }
  
  else if( root->m_data < key ) { 
    remove( key, root->m_right ); 
  }
  
  // Node with two children
  else if( root->m_left != NULL && root->m_right != NULL ) { // two children
    
    // find right’s lowest value
    root->m_data = findMin( root->m_right );
    // now delete that found value
    remove(root->m_data, root->m_right );
  }
 
  else {// Node with zero or one child
    BinaryNode *node = root;
    root = ( root->m_left != NULL ) ? root->m_left : root->m_right;
    delete node;
    //    node = NULL;
  }

}

// find(int key, BinaryNode * root) 
// Private version of find()
// Finds the key if it exists in the tree
// Returns true if it exists otherwise false
bool LazyBST::find(int key, BinaryNode *&root) {
  // if the tree is empty or reached the end and the key does not exist
  if (root == NULL){
    return false;
  }

  // if the key is less than the root, go left
  else if(root->m_data > key){
    return find(key, root->m_left);
  }

  // otherwise go right
  else if (root->m_data < key){
    return find(key, root->m_right);
  }
  
  else if (root->m_data == key){
    return true;
  }
  
}

// inorder(BinaryNode *root ostream & out) const;
// Private version of inorder()
// Prints the values using the inorder traversal
void LazyBST::inorder(BinaryNode *& root){// , ostream & out) const{
  if (root != NULL){
    cout << "(";
    inorder(root->m_left); 
    cout << root->m_data << ":" << root->m_height << ":"  << root->m_size;
    inorder(root->m_right); //(m_root->m_right);
    cout << ")" ;

  } 
}

// Name: rebalance1(BinaryNode *&root)
// PreCondition: Must be called by public function only
// PostCondition: Checks the conditions that must be true for
//                the tree to become balance
void LazyBST::rebalance1(BinaryNode *&root){
  if (root != NULL and root->m_left != NULL and root->m_right != NULL){
   
    int size = findSize(root);
    if (root->m_height > 3){//and
      if ((root->m_left->m_size >= 2*(root->m_right->m_size)) or (root->m_right->m_size >= 2*(root->m_left->m_size)) ) {

	m_storage =  new int[size]; // create enough space
	
	int i = 0;
	setup(root, m_storage, i); // put all the data in m_storage
	
	Empty(root);
	
	m_root = rebalance2(m_storage, 0, size-1); // finally balance using the data
    
	delete [] m_storage;
      }
    }
  }
}




// Name: setup(BinaryNode *&root, int index)
// PreCondition: Must be called by rebalance1 function only
// PostCondition: Sets up the m_storage array with all data
int LazyBST::setup(BinaryNode *&root, int *&list, int index){
  if(root == NULL)
    return index;

  if(root->m_left != NULL){
    index = setup(root->m_left, list, index);
  }

  list[index] = root->m_data;
  index++;

  if(root->m_right != NULL){
    index = setup(root->m_right, list, index);
  }

  return index;
}



// Name: rebalance2(BinaryNode *&root)
// PreCondition: Must be called by private rebalance1 function only
// PostCondition: Balances the tree
LazyBST::BinaryNode* LazyBST::rebalance2(int *&list, int start, int end){
  if (start > end){
    return NULL;
  }

  int middle = (start + end)/2;
  BinaryNode * newNode = new BinaryNode(list[middle], NULL, NULL);
  
  newNode->m_left = rebalance2(list, start, middle -1);
  
  newNode->m_right = rebalance2(list, middle+1, end);
  
  newNode->m_height = findHeight(newNode);
  newNode->m_size = findSize(newNode);
  return newNode;

}


// findMin(BinaryNode * root)
// Finds the minimum of the subtree 
int LazyBST::findMin(BinaryNode *&root){
  if (root == NULL){
    return NULL;
  }

  if (root->m_left == NULL){
    return root->m_data;
  }
  else {
    return findMin(root->m_left);
  }
}

// Empty(BinaryNode *root)
// Deletes the entire tree
void LazyBST::Empty(BinaryNode *&root){
  if (root != NULL){

    // If children exist, delete them
    if (root->m_left != NULL){
      Empty(root->m_left);
    }

    if (root->m_right != NULL){
      Empty(root->m_right);
    }

    // delete the node 
    delete root;
    root = NULL;
  }
}

// findHeight()
// finds the height of the tree and the subtree
int LazyBST::findHeight(BinaryNode *&root){ // determines the height of the subtree
  if (root == NULL)
    {
      return -1;
    }

  int left = findHeight(root->m_left);
  int right = findHeight(root->m_right); 

  return 1 + std::max(left, right);
}

// findSize()
// finds the number of nodes in the tree and subtree
int LazyBST::findSize(BinaryNode *&root){ // updates the size of the subtree
  if(!root) 
    return 0;
  else
    return findSize(root->m_left) + 1 + findSize(root->m_right); 
}


// BinaryNode functions

// Binary Node Constructor
// Creates a node with the given data
LazyBST::BinaryNode::BinaryNode(int data, BinaryNode *lt, BinaryNode *rt ){
  m_data = data;
  m_left = lt;
  m_right = rt;
}
 
