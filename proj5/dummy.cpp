# include <iostream>
# include <string>
using namespace std;

int main(){

  int num1 = 8;
  int * numPtr1 = &num1;
  int * numPtr2 = numPtr1;


  cout << "numPtr1 = " << *numPtr1 << endl;
  cout << "numPtr2 = " << *numPtr2 << endl;
  cout << " " << endl;

  int num2 = 10;
  numPtr1 = &num2;

  cout << "after changing numPtr1 to 10 " << endl;
  cout << "numPtr1 = " << *numPtr1 << endl;
  cout << "numPtr2 = " << *numPtr2 << endl;
  cout << " " << endl;

}
