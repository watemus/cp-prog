//
// Created by watemus on 23.11.2020.
//

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char **argv) {
  mt19937 rnd(atoi(argv[1]));
  int n = 3;
  cout << n << endl;
  for (int i = 0; i < n; i++) {
    int x = rnd() % 10;
    int y = rnd() % 10;
    cout << x << ' ' << y << endl;
  }
  return 0;
}