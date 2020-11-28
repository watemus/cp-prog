//
// Created by watemus on 13.11.2020.
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

void run() {
  int len, n;
  cin >> len >> n;
  vec<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  sort(ALL(a));
  vec<pair<int, int>> pr;
  pr.push_back({a[0], a[0]});
  int cln = 2;
  for (int i = 1; i < n; i++) {
    if (a[i] == a[i - 1] + 1) {
      pr.back().second = a[i];
    } else {
      pr.push_back({a[i], a[i]});
    }
  }
  cln += pr.size() - 1;
  for (auto pp : pr) {
    cln += to_string(pp.first).size();
    if (pp.first != pp.second) {
      cln += to_string(pp.second).size() + 1;
      if (pp.first + 1 < pp.second) {
        cln++;
      }
    }
  }
  while (cln > len) {
    int j = pr.size() - 2;
    int anst = INFL;
    for (int i = pr.size() - 2; i >= 0; i--) {
       if (pr[i + 1].first - pr[i].second - 1 < anst) {
         anst = pr[i + 1].first - pr[i].second - 1;
         j = i;
       }
    }
    auto nxt = pr[j + 1];
    pr.erase(pr.begin() + j + 1);
    if (pr[j].first != pr[j].second) {
      cln -= to_string(pr[j].second).size() + 1;
      if (pr[j].first + 1 < pr[j].second) {
        cln--;
      }
    }
    pr[j].second = nxt.second;
    if (nxt.first != nxt.second) {
      cln -= to_string(nxt.first).size() + 1;
      if (nxt.first + 1 < nxt.second) {
        cln--;
      }
    }
    cln--;
    cln += 2;
  }
  string res = "[";
  for (auto pp : pr) {
    res += to_string(pp.first);
    if (pp.first != pp.second) {
      if (pp.first + 1 < pp.second)
        res += "..";
      else
        res += ",";
      res += to_string(pp.second);
    }
    res += ",";
  }
  res.pop_back();
  res += ']';
//  cout << cln << '\n';
//  cout << res.size() << '\n';
  cout << res << '\n';
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


