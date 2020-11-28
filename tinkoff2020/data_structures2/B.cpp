//
// Created by watemus on 28.10.2020.
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

// #define int ll

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

const int T = 3.9e7;
const int L = 0;
const int R = 5e5 + 10;
const int MID = (L + R) / 2;

char agn[T];
int t[T], lt[T], rt[T];

int cnt_nodes = 0;

inline int new_node() {
  int v = cnt_nodes++;
  t[v] = 0;
  agn[v] = -1;
  lt[v] = -1;
  rt[v] = -1;
  return v;
}

inline int cpy_node(int u) {
  int v = cnt_nodes++;
  t[v] = t[u];
  agn[v] = agn[u];
  lt[v] = lt[u];
  rt[v] = rt[u];
  return v;
}

int build(int l, int r) {
  int v = new_node();
  if (r - l > 1) {
    int mid = (l + r) / 2;
    lt[v] = build(l, mid);
    rt[v] = build(mid, r);
    t[v] = t[lt[v]] + t[rt[v]];
  }
  return v;
}

int push(int v, int l, int r) {
  if (lt[v] == -1) lt[v] = new_node();
  if (rt[v] == -1) rt[v] = new_node();
  v = cpy_node(v);
  if (agn[v] != -1) {
    t[v] = agn[v] * (r - l);
    if (r - l > 1) {
      lt[v] = cpy_node(lt[v]);
      rt[v] = cpy_node(rt[v]);
      agn[lt[v]] = agn[v];
      agn[rt[v]] = agn[v];
    }
    agn[v] = -1;
  }
  return v;
}

int push2(int v, int l, int r) {
  if (lt[v] == -1) lt[v] = new_node();
  if (rt[v] == -1) rt[v] = new_node();
  if (agn[v] != -1) {
    t[v] = agn[v] * (r - l);
    if (r - l > 1) {
      lt[v] = cpy_node(lt[v]);
      rt[v] = cpy_node(rt[v]);
      agn[lt[v]] = agn[v];
      agn[rt[v]] = agn[v];
    }
    agn[v] = -1;
  }
  return v;
}

pair<int, int> descent(int v, int l, int r, int from) {
  if (lt[v] == -1) lt[v] = new_node();
  if (rt[v] == -1) rt[v] = new_node();
  if (agn[v] != -1)
    v = push(v, l, r);
  if (r <= from || t[v] == 0) {
    return {v, -1};
  }
  if (r - l == 1) {
    return {v, l};
  }
  int mid = (l + r) / 2;
  auto [u, ans] = descent(lt[v], l, mid, from);
  lt[v] = u;
  if (ans == -1) {
    tie(u, ans) = descent(rt[v], mid, r, from);
    rt[v] = u;
    return {v, ans};
  }
  return {v, ans};
}

int modify(int v, int l, int r, int lq, int rq, int x) {
  if (lt[v] == -1) lt[v] = new_node();
  if (rt[v] == -1) rt[v] = new_node();
  v = push(v, l, r);
  if (lq <= l && r <= rq) {
    agn[v] = x;
    v = push2(v, l, r);
    return v;
  } else if (l >= rq || r <= lq) {
    return v;
  } else {
    int mid = (l + r) / 2;
    lt[v] = modify(lt[v], l, mid, lq, rq, x);
    rt[v] = modify(rt[v], mid, r, lq, rq, x);
    t[v] = t[lt[v]] + t[rt[v]];
    return v;
  }
}

int roots[MID];
int attack[MID], hp[MID];
int cnt = 0;

int print(int v, int l, int r) {
  v = push(v, l, r);
  if (r - l == 1) {
    cout << t[v] << ' ';
  } else {
    int mid = (l + r) / 2;
    lt[v] = print(lt[v], l, mid);
    rt[v] = print(rt[v], mid, r);
  }
  return v;
}

void run() {
  int n;
  cin >> n;
  roots[cnt++] = new_node();
  roots[0] = modify(roots[0], L, R, MID, MID + 1, 1);
  vec<int> ans = {0};
  for (int i = 0; i < n; i++) {
    int typ;
    cin >> typ;
    if (typ == 1) {
      roots[cnt++] = (cpy_node(roots[0]));
      ans.push_back(-1);
    } else if (typ == 2) {
      int x;
      cin >> x;
      attack[x]++;
    } else if (typ == 3) {
      int x;
      cin >> x;
      hp[x]++;
    } else if (typ == 4) {
      int x;
      cin >> x;
      roots[cnt++] = (cpy_node(roots[x]));
      attack[cnt - 1] = (attack[x]);
      hp[cnt - 1] = (hp[x]);
      ans.push_back(ans[x]);
      if (ans.back() != -1) {
        ans.back() = i + 1;
      }
    } else {
      int x, y;
      cin >> x >> y;
      auto make_attack = [&](int a, int b) {
        int ll = MID - hp[b] + attack[a];
        auto [v, rr] = descent(roots[b], L, R, ll);
        roots[b] = v;
        if (rr == -1) {
          ans[b] = i + 1;
        } else {
          if (ll < rr) {
            roots[b] = modify(roots[b], L, R, ll, rr, 1);
          }
          roots[b] = modify(roots[b], L, R, rr, rr + 1, 0);
        }
        if (t[roots[b]] == 0) {
          ans[b] = i + 1;
        }
      };
      if (ans[x] == -1 && ans[y] == -1) {
        make_attack(x, y);
        make_attack(y, x);
      }
//      cout << endl;
    }
//    for (int j = 0; j < attack.size(); j++) {
//      print(roots[j], L, R);
//      cout << endl;
//    }
  }
  cout << ans.size() - 1 << '\n';
  for (int i = 1; i < ans.size(); i++) {
    cout << ans[i] << ' ';
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


