//
// Created by watemus on 30.09.2020.
//

#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif

#include <bits/stdc++.h>

using namespace std;


signed main(int argc, char **argv) {
  mt19937 rnd(atoi(argv[1]));
  int n = 3;
  cout << n << ' ' << n << endl;
  for (int i = 0; i < n * 2; i++) {
    cout << rnd() % 10 << ' ' << rnd() % 10 << endl;
  }
  return 0;
}


