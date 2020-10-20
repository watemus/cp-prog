//
// Created by watemus on 19.10.2020.
//

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
  int n = 5, k = rnd() % n + 1;
  cout << n << ' ' << k << endl;
  for (int i = 0; i < n; i++) {
    cout << rnd() % 10 + 1 << " ";
  }
  return 0;
}
