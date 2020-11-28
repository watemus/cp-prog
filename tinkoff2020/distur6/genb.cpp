#include <bits/stdc++.h>

using namespace std;

signed main(int argc, char **argv) {
  mt19937 rnd(atoi(argv[1]));
  int n = rnd() % 10 + 2;
  int m = (1 << n);
  cout << n << endl;
  vector<int> p(m);
  iota(p.begin(), p.end(), 0);
  shuffle(p.begin(), p.end(), rnd);
  for (int i = 0; i < m; i++) {
    cout << p[i] << ' ';
  }
  cout << '\n';
  return 0;
}