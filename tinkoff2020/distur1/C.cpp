//
// Created by watemus on 08.10.2020.
//

#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif

#include <bits/stdc++.h>

using namespace std;

#define ALL(a) a.begin(), a.end()
#define RALL(a) a.rbegin(), a.rend()
#define FF first
#define SS second

using ll = long long;
using ld = long double;

#define int ll

template<typename T>
using vec = std::vector<T>;

template<typename T>
using uset = std::unordered_set<T>;

template<typename T1, typename T2>
using umap = std::unordered_map<T1, T2>;

constexpr ll INFL = 1000000000000000228;
constexpr int INFI = 1000000228;
const ld PI = acos(-1);

#ifdef LOCAL
std::mt19937 rnd(228);
#else
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
#endif

vec<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

const int N = 1e5 + 10;

map<int, int> col[N];

int check(int a, int b) {
  int g = __gcd(a, b);
  a /= g;
  b /= g;
  if (a == 1)
    return b % 2;
  if (b == 1)
    return a % 2;
  if (col[a].count(b))
    return col[a][b];
  if (a > 1 && b > 1) {
    int rr = rnd() % 2;
    if (rr) {
      if (check(a - 1, b)) {
        col[a][b] = 0;
        return 0;
      } else if (check(a, b - 1)) {
        col[a][b] = 0;
        return 0;
      }
    } else {
      if (check(a, b - 1)) {
        col[a][b] = 0;
        return 0;
      } else if (check(a - 1, b)) {
        col[a][b] = 0;
        return 0;
      }
    }
  }
  if (a > 1 && check(a - 1, b))
    col[a][b] = 0;
  else if (b > 1 && check(a, b - 1))
    col[a][b] = 0;
  else
    col[a][b] = 1;
  return col[a][b];
}

void solve(int a, int b) {
  string t = "C";
  while (t != "OK" && t != "WA") {

    if (a > 1 && b > 1) {
      int rr = rnd() % 2;
      if (rr && check(a - 1, b)) {
        a--;
        cout << "A" << endl;
      } else if (rr) {
        b--;
        cout << "B" << endl;
      } else if (check(b - 1, a)) {
        b--;
        cout << "B" << endl;
      } else {
        cout << "A" << endl;
        a--;
      }
    }
    else if (b > 1 && check(a, b - 1)) {
      cout << "B" << endl;
      b--;
    } else {
      cout << "A" << endl;
      a--;
    }
    int g = __gcd(a, b);
    a /= g;
    b /= g;
    cin >> t;
    if (t == "A") {
      a--;
    } else if (t == "B") {
      b--;
    }
    g = __gcd(a, b);
    a /= g;
    b /= g;///////s///...
  }
}

void run() {
  int a, b;
  cin >> a >> b;
  col[1][1] = 1;
  solve(a, b);
}

signed main() {
#ifdef LOCAL
  //std::freopen("input.txt", "r", stdin);;;;
#else
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
#endif
  int t = 1;
  // cin >> t;
  while (t--) {
    run();
  }
  return 0;
}