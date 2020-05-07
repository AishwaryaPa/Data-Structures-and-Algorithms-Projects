/*****************************************
 ** File:    LazyBST.h
 ** Project: CMSC 341 Project 3, Spring 2017
 ** Author:  Aishwarya Panchumarty
 ** Date:    04/09/17
 ** Section: 03
 ** E-mail:  aispan1@umbc.edu
 **
 ** This file contains the class declarations 
 ** for Lazy Binary Tree and its subclass 
 ** BinaryNode
 ***********************************************/


#ifndef LAZYBST_H
#define LAZYBST_H


#include <iostream>
#include <cstring>
using namespace std;

class LazyBST{
  class BinaryNode; // forward inner class declaration
  
 public:
  // Name: Constructor
  // PreCondition: None
  // PostCondition: Creates an instance of Lazy Binary Tree
  LazyBST() ;

  // Name: Copy Constructor
  // PreCondition: None
  // PostCondition: Creates a deep copy of the object being called on
  LazyBST(const LazyBST &other) ;

  // Name: Destructor
  // PreCondition: Nodes must be dynamically allocated
  // PostCondition: All the nodes will deallocated
  ~LazyBST() ;

  // Name: Assignment Operator
  // PreCondition: None
  // PostCondition: Sets the object equal to the another object
  const LazyBST& operator=(const LazyBST& rhs) ;

  // Name: insert(int key)
  // PreCondition: The binary tree must exist
  // PostCondition: If the key is not a duplicate, then the 
  //                a node will be created and inserted in tree
  void insert (int key) ;

  // Name: remove(int key)
  // PreCondition: The binary tree must exist
  // PostCondition: Removes the node if it exists otherwise does nothing
  bool remove(int key) ;

  // Name: find()
  // PreCondition: Can only be used by class not by user
  // PostCondition: Returns true if key was found otherwise false
  bool find(int key) ;

  // Name: inorder()
  // PreCondition: The binary tree must exist
  // PostCondition: Prints the nodes using inorder transversal
  void inorder() ;

  // Name: locate(const char *position, int& key)
  // PreCondition: The binary tree must exist
  // PostCondition: Returns true if a key exists in the 
  //                given position. Otherwise false
  bool locate(const char *position, int& key) ;

 private:
  BinaryNode *m_root; // pointer to the root
  int *m_storage; 

  // Name: copy(const BinaryNode *other);
  // PreCondition: Must be called cpy constructor or assignment operator
  // PostCondition: Creates a deep copy
  LazyBST::BinaryNode* copy(const BinaryNode *other);

  // Name: locate()
  // PreCondition: Finds the key if it exists
  // PostCondition: returns a boolean value that tells whether the key exists or not
  bool locate(const char *position, int& key, int index, BinaryNode *&root);


  // Name: insert(int key, BinaryNode * root)
  // PreCondition: Must be called by public insert function only
  // PostCondition: Creates a new node and inserts it in the tree
  void insert(int key, BinaryNode * &root) ;

  // Name: remove(int key, BinaryNode * root)
  // PreCondition: Must be called by public remove function only
  // PostCondition: removes the node
  bool remove(int key, BinaryNode * &root) ;

  // Name: find(int key, BinaryNode * root)
  // PreCondition: Must be called by public find function only
  // PostCondition: Returns true if node exists otherwise false
  bool find(int key, BinaryNode * &root) ;

  // Name: inorder(BinaryNode * root)
  // PreCondition: Must be called by public inorder function only
  // PostCondition: Prints the nodes using the inorder transversal
  void inorder(BinaryNode * &root);

  // Name: rebalance1(BinaryNode *&root)
  // PreCondition: Must be called by public function only
  // PostCondition: Checks the conditions that must be true for
  //                the tree to become balance
  void rebalance1(BinaryNode *&root);

  // Name: setup(BinaryNode *&root)
  // PreCondition: Must be called by rebalance1 function only
  // PostCondition: Sets up the m_storage array with all data 
  int setup(BinaryNode *&root, int *&list, int index);

  // Name: rebalance2(BinaryNode *&root)
  // PreCondition: Must be called by private rebalance1 function only
  // PostCondition: Balances the tree
  LazyBST::BinaryNode* rebalance2(int *&list, int start, int end);

  // Name: findMin(BinaryNode *root)
  // PreCondition: Must be called be public functions only
  // PostCondition: Returns the minimum value of the given subtree
  int findMin(BinaryNode * &root);

  // Name: Empty(BinaryNode *root)
  // PreCondition: Must be called by public functions only
  // PostCondition: Empties the subtree
  void Empty(BinaryNode * &root);

  // Name: findHeight()
  // PreCondition: Node must exist
  // PostCondition: finds the height of the subtree
  int findHeight(BinaryNode * &root);
 
  // Name: findSize(int base, int depth)
  // PreCondition: Node must exist
  // PostCondition: finds the number of nodes in the subtree
  int findSize(BinaryNode *& root); 

  
  class BinaryNode {
    friend class LazyBST; 

  private:
    int m_data; // Data in the node
    BinaryNode *m_left; // Left child
    BinaryNode *m_right; // Right child

    int m_height; // height of the subtree
    int m_size; // number of nodes in the subtree of in entire tree


    // Name: Constructor for Binary Node
    // PreCondition: Must be called by public functions only
    // PostCondition: Creates a node 
    BinaryNode(int data, BinaryNode *lt, BinaryNode *rt );

  };

};

#endif
