//
// Created by watemus on 25.10.2020.
//
#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif

#include <bits/stdc++.h>

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("vpt")

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

constexpr ll INFL = 1000000000000000069;
constexpr int INFI = 1000000069;
const ld PI = acos(-1);

#ifdef LOCAL
std::mt19937 rnd(69);
#else
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
#endif

vec<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

const int N = 2e6 + 10;

const int K = 101;

int dp[N];

struct Exp {
  int l, r, c;
};

struct Min_q {
  deque<signed> dq;
  void push(int val) {
    while (dq.size() && dp[dq.back()] > dp[val]) {
      dq.pop_back();
    }
    dq.push_back(val);
  }
  void pop(int val) {
    if (dq.front() == val)
      dq.pop_front();
  }
  int get() {
    return dq.front();
  }
};

void run() {
  int n, a;
  cin >> n >> a;
  vec<Exp> exps(n);
  for (auto &exp : exps) {
    cin >> exp.l >> exp.r >> exp.c;
  }
  for (int i = 0; i <= a; i++) {
    dp[i] = ll(i * ll(1e9));
  }
  Min_q q[K];
  for (int i = a; i >= 0; i--) {
    for (int j = 0; j < n; j++) {
      if (i + exps[j].l <= a) {
        q[j].push(i + exps[j].l);
      }
      if (i + exps[j].r < a) {
        q[j].pop(i + exps[j].r + 1);
      }
      if (i + exps[j].r <= a) {
        dp[i] = max(dp[i], dp[q[j].get()] - exps[j].c);
      }
    }
  }

  cout << dp[0] << endl;
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


