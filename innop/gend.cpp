//
// Created by watemus on 22.11.2020.
//

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char **argv) {
  mt19937 rnd(atoi(argv[1]));
  int n = 4, q = 1;
  cout << n << ' ' << q << endl;
  vector<int> p(n);
  iota(p.begin(), p.end(), 1);
  shuffle(p.begin(), p.end(), rnd);
  for (int i = 0; i < n; i++) {
    cout << p[i] << ' ';
  }
  cout << endl;
  int x = rnd() % n + 1;
  int y = rnd() % n + 1;
  while (y == x) {
    y = rnd() % n + 1;
  }
  cout << x << ' ' << y << '\n';
  return 0;
}