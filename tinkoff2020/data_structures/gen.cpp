//
// Created by watemus on 05.10.2020.
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
    cout << rnd() % 6 << ' ';
  }
  int q = 2;
  cout << q << endl;
  cout << "C " << rnd() % n + 1 << ' ' << rnd() % 6 << endl;
  cout << "Q " << 1 << " " << 0 << " " << n << " " << rnd() % 6 + 1 << endl;
  return 0;
}
