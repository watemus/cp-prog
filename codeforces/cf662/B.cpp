//
// Created by watemus on 07.08.2020.
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

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;
const ld PI = acos(-1);
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

vec<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

const int MAXN = 3e5;

int t[MAXN * 4];

void modify(int v, int lb, int rb, int at, int dt) {
  if (rb - lb == 1) {
    t[v] += dt;
  } else {
    int mid = (lb + rb) / 2;
    if (at < mid)
      modify(v * 2 + 1, lb, mid, at, dt);
    else
      modify(v * 2 + 2, mid, rb, at, dt);
    t[v] = max(t[v * 2 + 1], t[v * 2 + 2]);
  }
}

pair<int, int> get(int v, int lb, int rb) {
  if (rb - lb == 1)
    return {lb, t[v]};
  int mid = (lb + rb) / 2;
  if (t[v * 2 + 1] > t[v * 2 + 2]) {
    return get(v * 2 + 1, lb, mid);
  } else {
    return get(v * 2 + 2, mid, rb);
  }
}

void run() {
  int n;
  cin >> n;
  memset(t, 0, sizeof t);
  for (int i = 0; i < n; i++) {
    int el;
    cin >> el;
    modify(0, 0, MAXN, el, 1);
  }
  int q;
  cin >> q;
  while (q--) {
    char type;
    int el;
    cin >> type >> el;
    if (type == '+') {
      modify(0, 0, MAXN, el, 1);
    } else {
      modify(0, 0, MAXN, el, -1);
    }
    auto [at, cnt] = get(0, 0, MAXN);
    if (cnt >= 4) {
      modify(0, 0, MAXN, at, -4);
      auto[att, cntt]= get(0, 0, MAXN);
      if (cntt >= 2) {
        modify(0, 0, MAXN, att, -2);
        auto [attt, cnttt] = get(0, 0, MAXN);
        if (cnttt >= 2) {
          cout << "YES\n";
        } else {
          cout << "NO\n";
        }
        modify(0, 0, MAXN, att, 2);
      } else {
        cout << "NO\n";
      }
      modify(0, 0, MAXN, at, 4);
    } else {
      cout << "NO\n";
    }
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
  //cin >> t;
  while (t--) {
    run();
  }
  return 0;
}


