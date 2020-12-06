//
// Created by watemus on 01../12.2020.
//

#include <bits/stdc++.h>

using namespace std;

signed main(int argc, char **argv) {
  mt19937 rnd(atoi(argv[1]));
  int n = 1e5, m = 1e5;
  cout << n << ' ' << m << endl;
  cout << 0 << ' ';
  for (int i = 1; i < n; i++) {
    cout << i - 1 << ' ';
  }
  cout << endl;
  for (int i = 0; i < n; i++) {
    cout << rnd() % 5 << ' ';
  }
  cout << endl;
  for (int i = 0; i < m; i++) {
    cout << rnd() % n << ' ' << rnd() % n << '\n';
  }
  return 0;
}