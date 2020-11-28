//
// Created by watemus on 01.11.2020.
//

#include <bits/stdc++.h>

using namespace std;

#define vec vector

signed main(int argc, char **argv) {
  mt19937 rnd(atoi(argv[1]));
  int ln = rnd() % int(1e4) + 1;
  vec<vec<int>> a;
  while (ln > 0) {
    int cr = rnd() % ln;
    if (ln == 1) cr = 1;
    ln -= cr;
    a.push_back({});
    for (int i = 0; i < cr; i++) {
      a.back().push_back(rnd() % int(2e9) - int(1e9));
    }
  }
  cout << a.size() << '\n';
  for (auto &row : a) {
    cout << row.size() << ' ';
    for (auto el : row) {
      cout << el << ' ';
    }
    cout << '\n';
  }
  return 0;
}