//
// Created by watemus on 14.12.2020.
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

struct Op {
  string op;
  int first;
  int second;
};

const int N = 5010;

int regs;
int at;
Op ops[N];

void apply() {
  string op = ops[at].op;
  int first = ops[at].first;
  int second = ops[at].second;
  if (op == "and") {
    int res = ((regs >> first) & (regs >> second)) & 1;
    regs ^= regs & (1 << first);
    regs ^= (res << first);
    at++;
  } else if (op == "or") {
    int res = ((regs >> first) | (regs >> second)) & 1;
    regs ^= regs & (1 << first);
    regs ^= (res << first);
    at++;
  } else if (op == "xor") {
    int res = ((regs >> first) ^ (regs >> second)) & 1;
    regs ^= regs & (1 << first);
    regs ^= (res << first);
    at++;
  } else if (op == "move") {
    int res = (regs >> second) & 1;
    regs ^= regs & (1 << first);
    regs ^= (res << first);
    at++;
  } else if (op == "set") {
    int res = second;
    regs ^= regs & (1 << first);
    regs ^= (res << first);
    at++;
  } else if (op == "not") {
    int res = !((regs >> first) & 1);
    regs ^= regs & (1 << first);
    regs ^= (res << first);
    at++;
  } else if (op == "jump") {
    if (regs & (1 << first)) {
      at = second;
    } else {
      at++;
    }
  } else {
    at++;
  }
}

int usd[N][N];

void run() {
  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n; i++) {
    cin >> ops[i].op;
    if (ops[i].op == "or" || ops[i].op == "xor" || ops[i].op == "and" || ops[i].op == "move" || ops[i].op == "set"
    || ops[i].op == "jump") {
      cin >> ops[i].first >> ops[i].second;
    }
    if (ops[i].op == "not") {
      cin >> ops[i].first;
    }
  }
  for (int i = 0; i < n; i++) {
    memset(usd[i], -1, sizeof usd[i]);
  }
  for (int mask = 0; mask < (1 << k); mask++) {
    at = 0;
    regs = mask;
    while (at < n && usd[at][regs] == -1) {
      usd[at][regs] = mask;
      apply();
    }
    if (at < n && usd[at][regs] == mask) {
      cout << "No\n";
      for (int i = 0; i < k; i++) {
        cout << ((mask & (1 << i)) >> i);
      }
      cout << '\n';
      return;
    }
  }
  cout << "Yes\n";
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


