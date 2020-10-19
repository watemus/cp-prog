//
// Created by watemus on 08.10.2020.
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
  int n = 5;
  cout << n << endl;
  vector<vector<int>> g(n);
  for (int i = 1; i < n; i++) {
    g[rnd() % i].push_back(i + 1);
  }
  for (int i = 0; i < n; i++) {
    cout << g[i].size() << ' ';
    for (auto u : g[i]) {
      cout << u << ' ';
    }
    cout << endl;
  }
  return 0;
}
