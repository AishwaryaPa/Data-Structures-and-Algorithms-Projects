# include <iostream>
# include <cstring>

using namespace std;

class Collection{
public:
  string **m_obj;
  int m_capacity;
  int size;

  Collection(int capacity){
    m_capacity = capacity;
    size = -1;
    m_obj = new string*[capacity];
  }

  void add(string item){
    size++;
    string * newItem = new string(item);
    m_obj[size] = newItem;
  }

  void dump(){
    for (int i = 0; i < m_capacity; i++){
      cout << "array[" << i << "]: " << *m_obj[i] << endl;
    }
    cout << " " << endl;
  }

  void remove(){
    for (int i = 0; i < m_capacity; i++){
      delete m_obj[i];
    }
    
    delete [] m_obj;
  }
  //private:
  //string m_objName;
};


int main(){
  Collection array1(2);
  Collection array2(3);

  Collection * array1Ptr = &array1;
  Collection * array2Ptr = &array2;

  
  array1Ptr->add("Lion");
  array1Ptr->add("Sheep");
  //  array1.add("Deer");


  array2Ptr->add("Lotus");
  array2Ptr->add("Rose");
  array2Ptr->add("Jasmine");

  // dump array 1 and 2
  cout << "Array 1" << endl;
  array1Ptr->dump();
  cout << "Array 2" << endl;
  array2Ptr->dump();

  array1Ptr->remove();
  //array2.remove();
    
  
  cout << " " << endl;
  cout << "swap array1 values with array2" << endl;

  array1Ptr = array2Ptr;
  array2Ptr = NULL;

  cout << "Array 1" << endl;
  array1Ptr->dump();

  if (array2Ptr == NULL){
    cout << "Array 2 is NULL" << endl;
  }
  else{
    cout << "Array 2" << endl;
    array2Ptr->dump();
  }


  cout << NULL << endl;
  array1Ptr->remove();
  //cout << "hey" << endl;
  //array2Ptr = NULL;
  //  cout << "hey2" << endl;
  return 0;
}
