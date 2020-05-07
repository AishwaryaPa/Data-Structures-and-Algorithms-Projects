# include <iostream>
# include <cstring>

using namespace std;

class Collection{
public:
  string m_obj;

  Collection(string obj){
    m_obj = obj;
  }

  //private:
  //string m_objName;
};


int main(){
  Collection ** array1 = new Collection*[3];
  Collection ** array2 = new Collection*[3];

  // create pointers for array1 to hold
  Collection * A1ptr1 = new Collection("Lion");
  Collection * A1ptr2 = new Collection("Sheep");
  Collection * A1ptr3 = new Collection("Rabbit");
  array1[0] = A1ptr1;
  array1[1] = A1ptr2;
  array1[2] = A1ptr3;

  // create pointer for array2 to hold
  // create pointers for array1 to hold
  Collection * A2ptr1 = new Collection("Ice-cream");
  Collection * A2ptr2 = new Collection("Yogurt");
  Collection * A2ptr3 = new Collection("Soup");
  array2[0] = A2ptr1;
  array2[1] = A2ptr2;
  array2[2] = A2ptr3;

  // dump array 1 and 2
  cout << "Array 1" << endl;
  cout << "array1[0]: " << array1[0]->m_obj << endl;
  cout << "array1[1]: " << array1[1]->m_obj << endl;
  cout << "array1[2]: " << array1[2]->m_obj << endl;
  cout << " " << endl;
  cout << "Array 2" << endl;
  cout << "array2[0]: " << array2[0]->m_obj << endl;
  cout << "array2[1]: " << array2[1]->m_obj << endl;
  cout << "array2[2]: " << array2[2]->m_obj << endl;
  cout << " " << endl;

  cout << " " << endl;
  cout << "swap array1 values with array2" << endl;
  array1[0] = array2[0];
  array1[1] = array2[1];
  array1[2] = array2[2];
  cout << "array1[0]: " << array1[0]->m_obj << endl;
  cout << "array1[1]: " << array1[1]->m_obj << endl;
  cout << "array1[2]: " << array1[2]->m_obj << endl;
  cout << " " << endl;
  
  cout << " " << endl;
  cout << "Does array2 still hold the values? " << endl;
  cout << "Array 2" << endl;
  cout << "array2[0]: " << array2[0]->m_obj << endl;
  cout << "array2[1]: " << array2[1]->m_obj << endl;
  cout << "array2[2]: " << array2[2]->m_obj << endl;
  cout << " " << endl;

  return 0;
}
