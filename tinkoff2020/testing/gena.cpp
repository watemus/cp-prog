//
// Created by watemus on 31.10.2020.
//

#include <bits/stdc++.h>

using namespace std;

signed main(int argc, char **argv) {
  mt19937 rnd(atoi(argv[1]));
  vector<int> fibs = {1, 1};
  for (int i = 2; i <= 30; i++) {
    fibs.push_back(fibs[i - 1] + fibs[i - 2]);
  }
  int n = rnd() % 100 + 10;
  cout << n << endl;
  for (int i = 0; i < n; i++) {
    if (rnd() % 2) {
      int el = rnd() % fibs.back() + 1;
      cout << el << '\n';
    } else {
      cout << fibs[rnd() % fibs.size()] << endl;
    }
  }
  return 0;
}