//
// Created by watemus on 29.09.2020.
//

//
// Created by watemus on 24.03.2020.
//

#include <bits/stdc++.h>

using namespace std;

signed main(int argc, char **argv) {
  mt19937 rnd(atoi(argv[1]));
  int n = 4;
  cout << n << endl;
  for (int i = 0; i < n; i++) {
    int cr = rnd() % 10 - 5;
    while (cr == 0) {
      cr = rnd() % 10 - 5;
    }
    cout << cr << ' ';
  }
  cout << endl;
  return 0;
}