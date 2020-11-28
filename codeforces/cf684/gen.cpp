#include <bits/stdc++.h>

using namespace std;

int main(int arcg, char **argv) {
  mt19937 rnd(atoi(argv[1]));
  cout << 1 << endl;
  int n = 5 + rnd() % 2;
  int m = 5 + rnd() % 2;
  cout << n << ' ' << m << endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cout << rnd() % 2;
    }
    cout << endl;
  }
  return 0;
}