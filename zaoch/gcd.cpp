//
// Created by watemus on 03.12.2020.
//

#include <iostream>

using namespace std;

int gcd(int a, int b) {
  if (a < b)
    swap(a, b);
  while (b > 0) {
    int tmp = a;
    a = b;
    b = tmp % b;
  }
  return a;
}

int main() {
  int a, b;
  cin >> a >> b;
  cout << gcd(a, b) << endl;
  return 0;
}