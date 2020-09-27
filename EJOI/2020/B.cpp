//
// Created by watemus on 06.09.2020.
//

#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif

#include <bits/stdc++.h>
#include "stub.h"

using namespace std;

#define ALL(a) a.begin(), a.end()
#define RALL(a) a.rbegin(), a.rend()
#define FF first
#define SS second

using ll = long long;
using ld = long double;

//#define int ll

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
/*
template<class... Args>
auto Vec(size_t n, Args&&... args) {
  if constexpr(sizeof...(args) == 1)
    return vector(n, args...);
  else
    return vector(n, Vec(args...));
}*/

#ifdef LOCAL
#else
#endif

bool check(int at, int n) {
  for (int i = 0; i <= n; i++) {
    if ((i + 1) % n == at || (at + 1) % n == i || at == i)
      continue;
    int res = query(at, i);
    if (res)
      return true;
  }
  return false;
}

int check_dist(int dist, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = i + 2; j < n; j++) {
      if ((i + 1) % n == j % n || (j + 1) % n == i || j % n == i)
        continue;
      int dst = max(i, n - j);
      if (i == 0) {
        dst = max(j, n - j);
      }
      if (dst == dist && query(i, j % n))
        return i * n + j % n;
    }
  }
  return false;
}

int solve(int n) {
  vec<int> have;
  for (int i = 2; i < n - 1; i++) {
    if (query(0, i)) {
      have.push_back(i);
    }
  }
  if (have.size() == 0) {
    return 1 + n * (n - 1);
  }
  if (have.size() == 1) {
    if (have[0] <= n / 2) {
      return n - 1 + have[0] * n;
    } else {
      return 1 + have[0] * n;
    }
  }
  pair<int, int> ans = {INFI, INFI};
  for (int i = 0; i < have.size(); i++) {
    ans = min(ans, make_pair(max(have[i], n - have[i]), have[i]));
  }
  for (int i = 1; i < have.size(); i++) {
    if (have[i] - have[i - 1] > 1)
      ans = min(ans, make_pair(max(have[i - 1], n - have[i]), have[i - 1] + have[i] * n));
  }
  return ans.second;
}



