//
// Created by watemus on 14.11.2020.
//

#include <bits/stdc++.h>

using namespace std;

signed main(int argc, char **argv) {
  int n = 250000;
  mt19937 rnd(atoi(argv[1]));
  if (rnd() % 2) {
    cout << '-';
  }
  for (int i = 0; i < n; i++) {
    cout << rnd() % 10;
  }
  cout << endl;
  if (rnd() % 2) {
    cout << '-';
  }
  for (int i = 0; i < n; i++) {
    cout << rnd() % 10;
  }
  cout << endl;
  return 0;
}