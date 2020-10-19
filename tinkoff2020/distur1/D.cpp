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

constexpr ld eps = 1e-5;

vec<int> div(vec<int> a) {
  vec<int> ans;
  int cr = 0;
  while (a.size()) {
    cr += a.back();
    a.pop_back();
    ans.push_back(cr / 2);
    cr %= 2;
    cr *= 10;
  }
  reverse(ALL(ans));
  while (ans.size() > 1 && ans.back() == 0) ans.pop_back();
  return ans;
}

vec<int> sub(vec<int> a, vec<int> b) {
  vec<int> ans(a.size());
  int cr = 0;
  for (int i = 0; i < 800; i++) {
    a[i] -= cr + (i < b.size() ? b[i] : 0);
    cr = a[i] < 0;
    if (cr)  a[i] += 2;
  }
  return a;
}

vec<int> add(vec<int> a, vec<int> b) {
  vec<int> ans(a.size());
  int cr = 0;
  for (int i = 0; i < 800; i++) {
    ans[i] = cr + a[i] + b[i];
    cr = ans[i] / 2;
    ans[i] %= 2;
  }
  return ans;
}

void run() {
  int n;
  cin >> n;
  vec<vec<int>> q(n);
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    vec<int> snum;
    for (auto ch : s) {
      snum.push_back(ch - '0');
    }
    reverse(ALL(snum));
    while (q[i].size() < 800) {
      q[i].push_back(0);
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
      q[i] = sub(q[i], q[j]);
    }
  }
  vec<int> p(n, -1);
  vec<int> one(800);
  one[0] = 1;
  vec<vec<int>> qq(n, one);
  for (int i = 1; i <= n; i++) {
    int cr = i - 1;
    int jj = n;
    for (int j = n - 1; j >= 0; j--) {
      if (p[j] != -1) {
        cr--;
      } else if (qq[j] == q[j]) {
        p[j] = i;
        jj = j;
        break;
      }
    }
    for (int j = jj + 1; j < n; j++) {
      if (p[j] == -1)
        qq[j] = add(qq[j], qq[jj]);
    }
  }
  for (int i = 0; i < n; i++) {
    cout << p[i] << ' ';
  }
}

signed main() {
#ifdef LOCAL
  std::freopen("input.txt", "r", stdin);
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


