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
  int n = 10;
  int q = 5;
  cout << n << ' '<< endl;
  for (int i = 0; i < n; i++) {
    cout << rnd() % 4 + 1 << ' ';
  }
  cout << endl;
  cout << q << endl;
  for (int i = 0; i < q; i++) {
    int t = rnd() % 3;
    int l = rnd() % n;
    int r = rnd() % n;
    int x = rnd() % 6 + 1;
    if (r < l) swap(l, r);
    if (t == 0) {
      cout << "reverse " << l + 1 << ' ' << r + 1 << endl;
    } else if (t == 1) {
      cout << "get " << l + 1 << ' ' << r + 1 << ' ' << x << endl;
    } else {
      cout << "set " << l + 1 << ' ' << r + 1 << ' ' << x << endl;
    }
  }
  return 0;
}
