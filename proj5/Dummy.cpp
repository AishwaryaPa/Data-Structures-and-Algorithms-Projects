/*****************************************
 ** File:    HashTable.h
 ** Project: CMSC 341 Project 5, Spring 2017
 ** Author:  Aishwarya Panchumarty
 ** Date:    05/1/17
 ** Section: 03
 ** E-mail:  aispan1@umbc.edu
 **
 ** This file contains the class implementations
 ** for HashTable class
 **
 ***********************************************/
# include "HashTable.h"
using namespace std;

char * const HashTable::DELETED  = (char *) 1 ;

// Default Constructor
HashTable::HashTable(int n) {

  // set size
  unsigned int capacity = static_cast<unsigned int>(n);

  if (capacity < MIN){
    capacity = 101;
  }

  else if(capacity > MAX){
    throw std::out_of_range("Size exceeds 199,999");
  }

  else if (capacity > MIN and capacity < MAX){
    capacity = nextPrime(0, numPrimes, capacity);
  }

  setArray(capacity);
}

// Destructor
HashTable::~HashTable(){
  cout << "HashTable destrctor" << endl;
  for (int i = 0; i < 3; i++){
    if (m_tables[i] != NULL){
      delete m_tables[i];
    }
  }
  
  delete [] m_tables;
}

// Copy Constructor
HashTable::HashTable (HashTable& other){
  if (other.isRehashing() == true){
    other.Rehash(2);
  }

  
  
}

// Assignment Operator
/*const HashTable& HashTable::operator= (HashTable& rhs){}
 */

// insert()
void HashTable::insert(const char *str){
  if(find2(str) == false){
    insert2(str); // then insert
  }

}

// find()
bool HashTable::find(const char *str){
  // check load factor first
  ManageLF();

  if(m_curr == FST_TB_INDEX){
    return searchTable(str, FST_TB_INDEX, false);
  }

  else if (m_curr == SEC_TB_INDEX){
    
    if (searchTable(str, FST_TB_INDEX, false) == true or searchTable(str, SEC_TB_INDEX, false) == true){
      return true;
    }

    else{
      return  false;
    }
  }
}

// remove()
char *HashTable:: remove(const char *str){
  //  ManageLF();
  if(find(str) == true){
    if(isRehashing() == false){
      return deleteVal(str, FST_TB_INDEX);
    }
    
    else{
      if (deleteVal(str, FST_TB_INDEX) != NULL){
	return deleteVal(str, FST_TB_INDEX);
      }
      
      else{
	return deleteVal(str, SEC_TB_INDEX);
      }
    }
  }
    
  else{
    return NULL;
  }
}

// isRehashing()
bool HashTable::isRehashing(){
  if(m_tables[SEC_TB_INDEX] != NULL){
    return true;
  }

  return false;
}

// tableSize()
int HashTable::tableSize(int table){
  if (table == 0){
    return m_tables[FST_TB_INDEX]->m_capacity;
  }

  else if (table == 1){
    if (isRehashing() == true){
      return m_tables[SEC_TB_INDEX]->m_capacity;
    }

    else{
      throw std::out_of_range("Request for non-existent tableSize");
    }
  }
}

// size()
int HashTable::size(int table){
  if (table == 0){
    return m_tables[FST_TB_INDEX]->m_size;
  }

  else if (table == 1){
    if (isRehashing() == true){
      return m_tables[SEC_TB_INDEX]->m_size;
    }

    else{
      throw std::out_of_range("Request for non-existent table size");
    }
  }
}

// at()
const char * HashTable::at(int index, int table){
  if (index < 0 or index >= m_tables[table]->m_capacity){
    throw std::out_of_range("index is invalid");
  }

  if (table >= 1 and isRehashing() == false){
    throw std::out_of_range("Request for non-existent table's value");
  }

  return m_tables[table]->m_data[index];
}

// dump()
void HashTable::dump(){
  cout << "HashTable #1: size = " << m_tables[FST_TB_INDEX]->m_size << ", tableSize = " << m_tables[FST_TB_INDEX]->m_capacity << endl;
  print(FST_TB_INDEX);
  cout << " " << endl;

  if (isRehashing() == true){
    cout << "HashTable #2: size = " << m_tables[SEC_TB_INDEX]->m_size << ", tableSize = " << m_tables[SEC_TB_INDEX]->m_capacity << endl;
    print(SEC_TB_INDEX);
    cout << " " << endl;
  }
}


//------------------------------------------------------------------------------------
// Private Functions
// nextPrime(int num);
// Finds the next prime number after the given number
int HashTable::nextPrime(int start, int end, int num){
  if(start != end){
    int middle = (start + end)/2;

    if (num < primes[middle] and num > primes[middle-1]){
      return primes[middle];
    }

    else if (num < primes[middle]){
      end = middle - 1;
      return nextPrime(start, end, num);
    }

    else if (num > primes[middle]){
      start = middle + 1;
      return nextPrime(start, end, num);
    }

    else if (num == primes[middle]){
      return num;
    }
  }

  return primes[start];
}

// setArray()
// Sets up the m_tables array so it can hold all
// the pointers to other tables
void HashTable::setArray(unsigned int capacity){
  m_tables = new Table *[3];

  Table * tablePtr1 = new Table(capacity);
  Table * tablePtr2 = NULL;
  Table * tablePtr3 = NULL;

  m_tables[FST_TB_INDEX] = tablePtr1;
  m_tables[SEC_TB_INDEX] = tablePtr2;
  m_tables[THD_TB_INDEX] = tablePtr3;

  m_curr = FST_TB_INDEX;
  m_insert = false;
}

//---------------Functions that handle direct operations on the HashTable -----------------

// find2()
bool HashTable::find2(const char *str){
  // check load factor first
  ManageLF();

  if(m_curr == FST_TB_INDEX){
    return searchTable(str, FST_TB_INDEX, true);
  }

  else if (m_curr == SEC_TB_INDEX){

    if (searchTable(str, FST_TB_INDEX, true) == true or searchTable(str, SEC_TB_INDEX, true) == true){
      return true;
    }

    else{
      return  false;
    }
  }
}


// Name: insert2()
// PreCondition:
// PostCondition:
void HashTable::insert2(const char *str){
  unsigned int index = hashCode(str) % m_tables[m_curr]->m_capacity;
  unsigned int position = index;
  bool stop = false;

  while(stop == false){
    position = validatePos(position, m_curr);

    if (m_tables[m_curr]->m_data[position] == NULL or m_tables[m_curr]->m_data[position] == DELETED){
      m_tables[m_curr]->m_data[position] = strdup(str);
      m_tables[m_curr]->m_size += 1;
      stop = true;
    }

    else{
      position += 1;
    }
  }

}

// insert3
// does not make copies
void HashTable::insert3(char *&value, int tableIndex){
  unsigned int place = hashCode(value) % m_tables[tableIndex]->m_capacity; // place keeps track of values in the new table
  bool stop = false;
  while(stop != true){

    place = validatePos(place, tableIndex);

    if (m_tables[tableIndex]->m_data[place] == NULL){ // if this place hasd not been taken
      m_tables[tableIndex]->m_data[place] = value;
      stop = true;
    }

    place += 1; // then search the next position
  }
}

// searchNewTable(const char* str);
// Private version of the find function. Searches the given value
bool HashTable::searchTable(const char* str, int tableIndex, bool fromInsert){
  unsigned int position = hashCode(str) % m_tables[tableIndex]->m_capacity;
  unsigned int index = position;
  bool found = false;
  int count  = 1;

  bool stop = false;
  while(stop != true){
    index = validatePos(index, tableIndex);
    if (m_tables[tableIndex]->m_data[index] == NULL ){
      stop = true;
    }

    else if(m_tables[tableIndex]->m_data[index] != DELETED and strcmp(m_tables[tableIndex]->m_data[index], str) == 0){
      stop = true;
      found = true;
    }

    else{
      index += 1;
      count += 1;
    }
  }
  
  if(fromInsert == true and found == false and isRehashing() == false and count >= 10){
    m_tables[tableIndex]->m_size += 1;
  }

  callFunc(count, tableIndex, position);
  
  return found;
}

// deleteVal
char * HashTable::deleteVal(const char * str, int tableIndex){
  unsigned int position = hashCode(str) % m_tables[tableIndex]->m_capacity;
  unsigned int index = position;
  bool stop = false;
  char * temp = NULL;
  int count = 1;

  while (stop != true){
    index = validatePos(index, tableIndex);
  
    if(m_tables[tableIndex]->m_data[index] == NULL){
      stop = true;
      return temp;
    }

    else if(m_tables[tableIndex]->m_data[index] != DELETED and strcmp(m_tables[tableIndex]->m_data[index], str) == 0){

      temp = m_tables[tableIndex]->m_data[index];
      m_tables[tableIndex]->m_size =  m_tables[tableIndex]->m_size - 1;
      m_tables[tableIndex]->m_data[index] = DELETED;
      stop = true;
      return temp;
    }

    else{
      index += 1;
      count += 1;
    }

  }

}


// print()
void HashTable::print(int tableIndex){
  for(unsigned int i = 0; i < m_tables[tableIndex]->m_capacity; i++){
    if(m_tables[tableIndex]->m_data[i] != NULL and m_tables[tableIndex]->m_data[i] != DELETED){
      cout << "H" << tableIndex + 1 << "[" << i << "] = " << m_tables[tableIndex]->m_data[i] << endl;
    }

    else if(m_tables[tableIndex]->m_data[i] == DELETED){
      cout << "H" << tableIndex + 1 << "[" << i << "] = DELETED" << endl;
    }

    else{
      cout << "H" << tableIndex + 1 << "[" << i << "] = "  << endl;
    }
  }
}


//--------------------Functions that handle the rehashing procedure ---------------------------------------------------

// createTable(unsigned int size, int newTbIndex)
//
//
void HashTable::createTable(unsigned int size, int newTbIndex){
  Table * tablePtr = new Table(nextPrime(0, numPrimes, size));
  m_tables[newTbIndex] = tablePtr;
  m_curr = newTbIndex;
}

void HashTable::callFunc(int count, int tableIndex, unsigned int position){
  if (count >= 10){
    ManageClusters(position, tableIndex);
  }

  else if(m_tables[tableIndex]->m_data[position] != NULL and m_tables[tableIndex]->m_data[position] != DELETED 
	  and tableIndex == FST_TB_INDEX and m_tables[SEC_TB_INDEX] != NULL){
    ManageClusters(position, tableIndex);
  }
}

// ManageLF()
// check if the load factor has reached .5 and if it did, creates new table
// if load factor has not reached .5 and in rehashing mode, then check the
// old tables' load factor if it is less than 0.03, then move the values in
// to the new table
void HashTable::ManageLF(){
  double ldFactor = static_cast<double>(m_tables[m_curr]->m_size) / static_cast<double>(m_tables[m_curr]->m_capacity);
  if (ldFactor >= 0.5){

    if (m_curr == FST_TB_INDEX){ // Not in rehash mode yet, so create a new table
      createTable(((m_tables[m_curr]->m_size) * 4), SEC_TB_INDEX);
    }
    
    else if (m_curr == SEC_TB_INDEX){ // already in the rehashing mode, so consolidate two tables into one
      Rehash(SEC_TB_INDEX);
    }
  }

  else if (ldFactor < 0.5 and m_curr == SEC_TB_INDEX){ // already in rehashing mode and the old tables' load factoc is less than 3%
    ldFactor = static_cast<double>(m_tables[FST_TB_INDEX]->m_size) / static_cast<double>(m_tables[FST_TB_INDEX]->m_capacity);

    if (ldFactor <= 0.03){
      Rehash(FST_TB_INDEX);
    }
  }
}

// ManageClusters(unsigned int hashPos)
//
void HashTable::ManageClusters(unsigned int hashPos, int tableIndex){
  if (tableIndex == FST_TB_INDEX and m_tables[tableIndex]->m_data[hashPos] != NULL){
    unsigned int start = findStart(hashPos, tableIndex); // find where the cluster begins and ends
    unsigned int end = findEnd(hashPos, tableIndex);

    if(isRehashing() == false){
      createTable(((m_tables[tableIndex]->m_size) * 4), SEC_TB_INDEX);
    }
    copy2(start, end, FST_TB_INDEX, SEC_TB_INDEX);  // copy into the new table
  }

  else if (tableIndex == SEC_TB_INDEX){ // if clusters were found in the new hash table
    Rehash(SEC_TB_INDEX);
  }
}


// Name: Rehash(int tableIndex);
// PreCondition: Expecting at least one table to be populated
// PostCondition: Repairs the hash table depending on the situation
void HashTable::Rehash(int tableIndex){
  // if there are two hash tables and the first hash table has reached lf of 0.3
  if (tableIndex == FST_TB_INDEX){
    copy(0, m_tables[FST_TB_INDEX]->m_capacity - 1, FST_TB_INDEX, SEC_TB_INDEX);

    Table * temp = m_tables[FST_TB_INDEX];
    delete temp;

    m_tables[FST_TB_INDEX] = m_tables[SEC_TB_INDEX];
    m_tables[SEC_TB_INDEX] = NULL;

    m_curr = FST_TB_INDEX;
  }
  // if the second table has reached a load factor of .5 or greater
  // or if there are clusters in it
  else if (tableIndex == SEC_TB_INDEX){
    // create third table
    unsigned int total = (m_tables[FST_TB_INDEX]->m_size + m_tables[SEC_TB_INDEX]->m_size) * 4;
    createTable(total, THD_TB_INDEX);
    
    // copy first tables and second tables' elements into the third table and deallocate the first and second table
    copy(0, m_tables[FST_TB_INDEX]->m_capacity - 1, FST_TB_INDEX, THD_TB_INDEX);
    Table * temp = m_tables[FST_TB_INDEX];
    delete temp;

    copy(0, m_tables[SEC_TB_INDEX]->m_capacity - 1, SEC_TB_INDEX, THD_TB_INDEX);
    Table * temp2 = m_tables[SEC_TB_INDEX];
    delete temp2;

    // set the first table pointer equal to the third table
    m_tables[FST_TB_INDEX] = m_tables[THD_TB_INDEX];

    // set second table ptr and third table ptr to NULL
    m_tables[SEC_TB_INDEX] = NULL;
    m_tables[THD_TB_INDEX] = NULL;

    // set m_curr equal to zero.
    m_curr = FST_TB_INDEX;

  }
}

// validatePos(unsigned int position, int tableIndex);
//
unsigned int HashTable::validatePos(unsigned int position, int tableIndex){
  if (position >= m_tables[tableIndex]->m_capacity){
    position = 0;
  }

  return position;
}

//
unsigned int HashTable::findStart(unsigned int index, int tableIndex){
  bool stop = false;
  while(stop == false){

    if (index == -1){
      stop = true;
      index = 0;
    }

    else{
      if(m_tables[tableIndex]->m_data[index] == NULL){
        stop = true;
        index += 1;
      }

      else{
        index -= 1;
      }
    }
  }
  return index;
}

unsigned int HashTable::findEnd(unsigned int index, int tableIndex){
  bool stop = false;
  while(stop == false){
    index = validatePos(index, tableIndex);

    if (m_tables[tableIndex]->m_data[index] == NULL){
      index -= 1;

      if(index == -1){
        index = (m_tables[tableIndex]->m_capacity) - 1;
      }

      stop = true;
    }

    else{
      index += 1;
    }
  }

  return index;
}

unsigned int HashTable::findSize(unsigned int start, unsigned int end){
  unsigned int difference = 0;
  if(end < start){
    difference = start - end;
    difference = (m_tables[m_curr]->m_capacity - 1) - difference;
  }
  else if(end > start){
    difference = (end - start) + 1;
  }

  return difference;
}


// copies from first function to second function
void HashTable::copy(unsigned int start, unsigned int end, int firstTable, int secondTable){
  unsigned int index = start;
  while(index != end + 1){
    index = validatePos(index, firstTable); // index keeps track of values in the old table
    if (m_tables[firstTable]->m_data[index] != NULL and m_tables[firstTable]->m_data[index] != DELETED){
      
      insert3(m_tables[firstTable]->m_data[index], secondTable);
      m_tables[firstTable]->m_data[index] = NULL;

      m_tables[firstTable]->m_size -= 1; // decrease the size of the old table
      m_tables[secondTable]->m_size += 1; // increase the size of the new table
    }

    else{
      index += 1;
    }
  }
}

// copies from first function to second function
void HashTable::copy2(unsigned int start, unsigned int end, int firstTable, int secondTable){
  unsigned int index = start;
  unsigned int difference = findSize(start, end);
  unsigned int count = 1;

  while(count != difference + 1){
    index = validatePos(index, firstTable); // index keeps track of values in the old table
    if (m_tables[firstTable]->m_data[index] != NULL and m_tables[firstTable]->m_data[index] != DELETED){
      insert3(m_tables[firstTable]->m_data[index], secondTable);
      m_tables[firstTable]->m_data[index] = NULL;

      m_tables[firstTable]->m_size -= 1; // decrease the size of the old table
      m_tables[secondTable]->m_size += 1; // increase the size of the new table
    }

    index += 1;
    count += 1;
  }

}

//-------------------------------------------------------------------------------------------------------
// Table class and its private functions

// Name: Constructor
// PreCondition:
// PostCondition:
HashTable::Table::Table(int capacity){
  if (capacity > MAX){
    throw std::out_of_range("Size surpassed 199, 999");
  }

  m_size = 0;
  m_capacity = capacity;

  m_data = new char *[m_capacity];

  for(int i = 0; i < capacity; i++){
    m_data[i] = NULL;
  }
}


// Name: Destructor
// PreCondition:
// PostCondition:
HashTable::Table::~Table(){
  deleteTable();
}

void HashTable::Table::deleteTable(){
  cout << "Table destructor" << endl;
  for(unsigned int i = 0; i < m_capacity; i++){
    if (m_data[i] != NULL and m_data[i] != HashTable::DELETED){
      free(m_data[i]);
    }
  }

  delete [] m_data;
}
