//
// Created by watemus on 05.11.2020.
//

#include <iostream>

using namespace std;

int main() {
  int n;
  cin >> n;
  cout << n << ' ';
  if (n > 10 && n <= 20) {
    cout << "korov";
  } else if (n % 10 == 1) {
    cout << "korova";
  } else if (n % 10 <= 4 && n % 10 != 0) {
    cout << "korovy";
  } else {
    cout << "korov";
  }
  cout << endl;
  return 0;
}