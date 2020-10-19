//
// Created by watemus on 16.10.2020.
//

//
// Created by watemus on 11.10.2020.
//

//
// Created by watemus on 11.10.2020.
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
  int n = 4;
  int q = 1;
  cout << n << ' '<< endl;
  for (int i = 0; i < n; i++) {
    cout << rnd() % 4 + 1 << ' ';
  }
  cout << endl;
  cout << q << endl;
  for (int i = 0; i < q; i++) {
    if (rnd() % 2) {
      int m = rnd() % 4 + 1;
      int l = rnd() % n + 1;
      int r = rnd() % n + 1;
      if (l > r) swap(l, r);
      cout << "2 " << m << ' ' << l << ' ' << r << '\n';
    } else {
      int ii = rnd() % n + 1;
      int x = rnd() % 4 + 1;
      cout << "1 " << ii << ' ' << x << '\n';
    }
  }
  return 0;
}
