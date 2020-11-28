//
// Created by watemus on 27.11.2020.
//

#include <bits/stdc++.h>

using namespace std;

signed main(int argc, char **argv) {
  mt19937 rnd(atoi(argv[1]));
  int n = 3.5e5;
  int m = 3.5e5;
  cout << n << ' ' << m << endl;
  for (int i = 0; i < m; i++) {
    cout << char('a');
  }
  cout << endl;
  for (int i = 0; i < n; i++) {
    cout << char('a');
  }
  cout << endl;
  for (int i = 2; i <= n; i++) {
    int pr = rnd() % (i - 1) + 1;
    cout << pr << ' ';
  }
  cout << endl;
  return 0;
}