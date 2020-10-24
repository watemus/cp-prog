//
// Created by watemus on 23.10.2020.
//

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
  int n = 10, m = 5;
  cout << n << ' ' << m << endl;
  char tt[n][m];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int t = rnd() % 4;
      if (t == 0)
        tt[i][j] = '(';
      else if (t == 1)
        tt[i][j] = ')';
      else if (t == 2)
        tt[i][j] = '*';
      else
        tt[i][j] = '.';
    }
  }
  tt[n - 1][rnd() % m] = 'M';
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cout << tt[i][j];
    }
    cout << endl;
  }
  return 0;
}
