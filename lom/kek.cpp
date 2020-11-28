//
// Created by watemus on 12.11.2020.
//

#include <bits/stdc++.h>

using namespace std;

signed main() {
  int n;
  cin >> n;
  int ans = 0;
  while (n > 0) {
    ans += n % 10;
    n /= 10;
  }
  cout << ans << '\n';
  return 0;
}