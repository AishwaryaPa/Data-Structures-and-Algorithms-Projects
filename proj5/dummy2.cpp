# include <iostream>
# include <cstring>

using namespace std;

int main(){
  int ** array1 = new int*[3];
  int ** array2 = new int*[3];

  // create pointers for array1 to hold
  int * A1ptr1 = new int(1);
  int * A1ptr2 = new int(2);
  int * A1ptr3 = new int(3);
  array1[0] = A1ptr1;
  array1[1] = A1ptr2;
  array1[2] = A1ptr3;

  // create pointer for array2 to hold
  int * A2ptr1 = new int(4);
  int * A2ptr2 = new int(5);
  int * A2ptr3 = new int(6);


  array2[0] = A2ptr1;
  array2[1] = A2ptr2;
  array2[2] = A2ptr3;


  // dump array 1 and 2
  cout << "Array 1" << endl;
  cout << "array1[0]: " << *array1[0] << endl;
  cout << "array1[1]: " << *array1[1] << endl;
  cout << "array1[2]: " << *array1[2] << endl;
  cout << " " << endl;
  cout << "Array 2" << endl;
  cout << "array2[0]: " << *array2[0] << endl;
  cout << "array2[1]: " << *array2[1] << endl;
  cout << "array2[2]: " << *array2[2] << endl;
  cout << " " << endl;

  cout << " " << endl;
  cout << "swap array1 values with array2" << endl;
  array1[0] = array2[0];
  array1[1] = array2[1];
  array1[2] = array2[2];
  cout << "array1[0]: " << *array1[0] << endl;
  cout << "array1[1]: " << *array1[1] << endl;
  cout << "array1[2]: " << *array1[2] << endl;
  cout << " " << endl;
  
  cout << " " << endl;
  cout << "Does array2 still hold the values? " << endl;
  cout << "Array 2" << endl;
  cout << "array2[0]: " << *array2[0] << endl;
  cout << "array2[1]: " << *array2[1] << endl;
  cout << "array2[2]: " << *array2[2] << endl;
  cout << " " << endl;

  return 0;
}
