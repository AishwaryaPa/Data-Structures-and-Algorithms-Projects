/*************************************
 ** File:    HashTable.h
 ** Project: CMSC 341 Project 5, Spring 2017
 ** Author:  Aishwarya Panchumarty
 ** Date:    05/1/17
 ** Section: 03
 ** E-mail:  aispan1@umbc.edu
 **
 ** This file contains the class declarations
 ** for HashTable class
 **
 ***********************************************/
#ifndef HASHTABLE_H
#define HASHTABLE_H

# include <iostream>
# include <cstring>
# include <cmath>
# include <stdexcept>
# include <cstdlib>
# include "primes.h"
//# include "words.h"
using namespace std;

const unsigned int MAX = 200000;
const unsigned int MIN = 101;
const int FST_TB_INDEX = 0;
const int SEC_TB_INDEX = 1;
const int THD_TB_INDEX = 2;

class HashTable{

  class Table; // inner class declaration

 public:
  static char * const DELETED;

  // Name: Default Constructor
  // PreCondition:
  // PostCondition:
  HashTable(int n=101) ;

  // Name: Destructor
  // PreCondition:
  // PostCondition:
  ~HashTable() ;

  // Name: Copy Constructor
  // PreCondition:
  // PostCondition:
  HashTable (HashTable& other) ;

  // Name: Assignment Operator
  // PreCondition:
  // PostCondition:
  const HashTable& operator= (HashTable& rhs) ;

  // Name: insert()
  // PreCondition:
  // PostCondition:
  void insert(const char *str) ;

  // Name: find()
  // PreCondition:
  // PostCondition:
  bool find(const char *str) ;

  // Name: remove()
  // PreCondition:
  // PostCondition:
  char * remove(const char *str) ;

  // Name: isRehashing()
  // PreCondition: None 
  // PostCondition: Returns true if there is an ongoing incremental rehash
  bool isRehashing() ;

  // Name: tableSize()
  // PreCondition: None
  // PostCondition: Returns the size of the hash table. When there is an ongoing 
  //                rehash, tableSize(0) should return the size of the old 
  //                table and tableSize(1) should return the size of the new table.
  int tableSize(int table=0) ;

  // Name: size()
  // PreCondition: None
  // PostCondition: Returns the number of items currently in the table(s)
  int size(int table=0) ;

  // Name: at()
  // PreCondition:
  // PostCondition: returns a pointer to the string stored at the index slot of 
  //                the hash table specified by table. If the index is invalid 
  //                (i.e., less than 0 or greater than or equal to table size), 
  //                then at() should throw an out_of_range exception (already defined in stdexcept). 
  const char * at(int index, int table=0) ;

  // Name: dump()
  // PreCondition:
  // PostCondition:
  void dump() ;

 private:
  
  
  Table ** m_tables; // table that holds all the pointers to the tables

  int m_curr; // index that keeps track of which table is currently being used 
 
  // Name: hashCode(const char *str)
  // PreCondition: 
  // PostCondition: converts a string into an integer
  unsigned int hashCode(const char *str) {

    unsigned int val = 0 ;
    const unsigned int thirtyThree = 33 ;  // magic number from textbook

    int i = 0 ;
    while (str[i] != '\0') {
      val = val * thirtyThree + str[i] ;
      i++ ;
    }
    return val ;
  }  


  // Name: nextPrime(int num);
  // PreCondition: None
  // PostCondition: Finds the next prime number after the given number
  int nextPrime(int start, int end, int prime);

  // Name: setArray()
  // PreCondition: Should only be called once from the constructor
  // PostCondition: Sets up the m_tables array so it can hold all 
  //                the pointers to other tables 
  void setArray(unsigned int capacity);

  // Name: find2()
  // PreCondition: Must be called by insert function only
  // PostCondition: Finds the value
  bool find2(const char *str);

  // Name: insert2(const char *str)
  // PreCondition: Load factor should have been already checked
  // PostCondition: Inserts the given string into the table
  void insert2(const char *str);

  // Name: insert3()
  // PreCondition: Takes the pointers from one table and puts it aanother table
  // PostCondition: Does not make copies. Simply changes the location of the pointer
  void insert3(char *&value, int tableIndex);

  // Name: SearchTable()
  // PreCondition: searches through the table if the value is in the table
  // PostCondition: Returns true if value was found else false
  bool searchTable(const char* str, int tableIndex, bool fromInsert);

  // Name: deleteVal
  // PreCondition: None
  // PostCondition: deletes the value if it exists
  char * deleteVal(const char * str, int tableIndex);

  // Name: print
  // PreCondition: None
  // PostCondition: Prints the table
  void print(int tableIndex);

  // Name: callFunc()
  // PreCondition: Must be called searchTable only
  // PostCondition: calls manageCluster if neccessary
  void callFunc(int count, int tableIndex, unsigned int position);
 
  // Name: createTable
  // PreCondition: None
  // PostCondition: Creates the table with given table
  void createTable(unsigned int size, int newTbIndex);

  // Name: ManageLF()
  // PreCondition: m_tables must be populated
  // PostCondition: Creates a new table if the current table is full. 
  //                If both tables are full, creates a third table
  void ManageLF();  

  // Name: ManageClusters()
  // PreCondition: None
  // PostCondition: Manages clusters depending on the situations
  void ManageClusters(unsigned int hashPos, int tableIndex);

  // Name: Rehash(int numTables);
  // PreCondition: Expecting at least one table to be populated
  // PostCondition: Repairs the hash table depending on the situation
  void Rehash(int tableIndex);

  // Name: ValidatePos
  // PreCondition: None
  // PostCondition: Sets index to zero if the at the end of table, otherwise return the index
  unsigned int validatePos(unsigned int position, int tableIndex);

  // Name: find start
  // PreCondition: index value must have a string in it. It should not be NULL
  // PostCondition: finds the start index
  unsigned int findStart(unsigned int index, int tableIndex);

  // Name: findEnd()
  // PreCondition: index value must have a string in it. It should not be NULL
  // PostCondition: finds the end index
  unsigned int findEnd(unsigned int index, int tableIndex);

  // Name: findSize()
  // PreCondition: Start and end must be valid
  // PostCondition: returns the size of the cluster
  unsigned int findSize(unsigned int start, unsigned int end);

  // Name: copy()
  // PreCondition: None
  // PostCondition: copies from table to another
  void copy(unsigned int start, unsigned int end, int firstTable, int secondTable);

  // Name: copy2
  // PreCondition: used for clusters only
  // PostCondition: Moves the pointers from one table to another
  void copy2(unsigned int start, unsigned int end, int firstTable, int secondTable);

  class Table{
    friend class HashTable;

  private:
    int m_size; // number of items in the table 
    unsigned int m_capacity; // the max number of items that can be stored in the table

    char ** m_data; // dynamic array that holds the data

    // Name: Table(int size);
    // PreCondition: Creates a table object
    // PostCondition:
    Table(int capacity);

    // Name: ~Table; Destructor
    // PreCondition:
    // PostCondition: Deallocates the memory
    ~Table();

    // Name: deleteTable();
    // PreCondition: Must be called by destructor
    // PostCondition: deallocates space
    void deleteTable();
    
  };

};

#endif
