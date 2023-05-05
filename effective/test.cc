#include <iostream>

using namespace std;

int main() {
  
  cin.setstate(cin.rdstate() | ios::badbit);
  try {
    cin.exceptions(ios::badbit);
    cout << "Success \n" ;
  } catch (ios_base::failure &error) {
    cout << "My error is " << error.what() << "\n";
  }
  return 0;
}