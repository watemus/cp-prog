#ifdef lolipop
#define _GLIBCXX_DEBUG
#endif

/*
    This ain't a milly rock
    This a money dance
    And my D' ain't hard
    That's a .30 in my pants
*/

#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>
#include <set>
#include <map>
#include <ctime>
#include <unordered_map>
#include <random>
#include <iomanip>
#include <cmath>
#include <queue>
#include <unordered_set>
#include <cassert>
#include <bitset>
#include <deque>
#include <utility>

#define int long long
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define ld long double

using namespace std;

mt19937 rnd(229);

inline void fastio() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
}

const int inf = 2e9 + 123;

struct beats {
  beats *l = nullptr, *r = nullptr;
  int m1 = 0, m2 = inf, cnt = 0;
  int sum = 0;
  int newmin = -1;
  int lb, rb;
  beats() {}
  beats(int L, int R) {
    lb = L, rb = R;
    cnt = rb - lb;
    if (lb + 1 < rb) {
      int m = (lb + rb) / 2;
      l = new beats(lb, m);
      r = new beats(m, rb);
    }
  }
  void push() {
    if (newmin == -1) return;
    sum += (newmin - m1) * cnt;
    m1 = newmin;
    if (lb + 1 < rb) {
      if (l->m1 < newmin) l->newmin = max(l->newmin, newmin);
      if (r->m1 < newmin) r->newmin = max(r->newmin, newmin);
    }
    newmin = -1;
  }
  void recount() {
    push();
    if (lb + 1 < rb) {
      l->push();
      r->push();
      sum = l->sum + r->sum;
      if (l->m1 == r->m1) {
        m1 = l->m1;
        cnt = l->cnt + r->cnt;
        m2 = min(l->m2, r->m2);
      } else {
        if (l->m1 < r->m1) {
          m1 = l->m1;
          cnt = l->cnt;
          m2 = r->m1;
        } else {
          m1 = r->m1;
          cnt = r->cnt;
          m2 = l->m1;
        }
      }
    }
  }
  void maxr(int L, int R, int x) {
    push();
    if (lb >= R || L >= rb) return;
    if (L <= lb && R >= rb && x <= m1) {
      return;
    }
    if (L <= lb && R >= rb && x > m1 && x < m2) {
      newmin = x;
      push();
      return;
    }
    l->maxr(L, R, x);
    r->maxr(L, R, x);
    recount();
  }
  int get(int L, int R) {
    push();
    if (lb >= R || L >= rb) return 0;
    if (L <= lb && R >= rb) return sum;
    return l->get(L, R) + r->get(L, R);
  }
};

int gcd(int a, int b) {
  while (b) {
    a %= b;
    swap(a, b);
  }
  return a;
}

void solve() {
  int n, m;
  while (cin >> n >> m) {
    if (n == 0 && m == 0) break;
    beats *root = new beats(0, n);
    while (m--) {
      char c;
      cin >> c;
      if (c == '?') {
        int l, r;
        cin >> l >> r;
        int a = root->get(l - 1, r), b = r + 1 - l;
        int g = gcd(a, b);
        a /= g;
        b /= g;
        if (b == 1) {
          cout << a << '\n';
        } else {
          cout << a << '/' << b << '\n';
        }
      } else {
        int l, r, x;
        cin >> l >> r >> x;
        root->maxr(l - 1, r, x);
      }
    }
  }
}

signed main() {
#ifdef lolipop
  freopen("input.txt", "r", stdin);
#else
  fastio();
#endif

  int T = 1;
//    cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}