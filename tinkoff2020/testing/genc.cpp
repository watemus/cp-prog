//
// Created by watemus on 01.11.2020.
//

#include <bits/stdc++.h>

using namespace std;

signed main(int argc, char **argv) {
  mt19937 rnd(atoi(argv[1]));
  int n = rnd() % int(1e5) + 1;
  for (int i = 0; i < n; i++) {
    cout << char('a' + rnd() % 26);
  }
  cout << endl;
  return 0;
}