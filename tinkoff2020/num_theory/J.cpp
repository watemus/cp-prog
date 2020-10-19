//
// Created by watemus on 01.10.2020.
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
using ull = unsigned long long;

#define int ull

template<typename T>
using vec = std::vector<T>;

template<typename T>
using uset = std::unordered_set<T>;

template<typename T1, typename T2>
using umap = std::unordered_map<T1, T2>;

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;
const ld PI = acos(-1);

#ifdef LOCAL
std::mt19937 rnd(228);
#else
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());
#endif

vec<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

template<class... Args>
auto Vec(size_t n, Args&&... args) {
  if constexpr(sizeof...(args) == 1)
    return vector(n, args...);
  else
    return vector(n, Vec(args...));
}

#ifdef LOCAL
#else
#endif

const int MAXN = 1e5 + 10;

int pw(int a, int b) {
  int ans = 1;
  while (b) {
    if (b & 1) {
      ans *= a;
    }
    a *= a;
    b >>= 1;
  }
  return ans;
}

void run() {
  vec<int> cnt(MAXN), d(MAXN);
  int n;
  cin >> n;
  n++;
  for (int i = 0; i < n; i++) {
    int el;
    cin >> el;
    cnt[el] = 1;
  }
  for (int i = 1; i < MAXN; i++) {
    for (int j = i; j < MAXN; j += i) {
      d[i] += cnt[j];
    }
  }
  int anss = 0;
  vec<int> ans[2];
  ans[0].resize(MAXN);
  ans[1].resize(MAXN);
  for (int i = MAXN - 1; i >= 1; i--) {
    if (d[i] == 1) {
      ans[1][i] = 1;
    } else if (d[i] > 1) {
      ans[0][i] = ans[1][i] = pw(2, d[i] - 1) - 1;
    }
    for (int j = i * 2; j < MAXN; j += i) {
      ans[1][i] -= ans[1][j];
      ans[0][i] -= ans[0][j];
    }
    anss += i * ans[1][i] - i * ans[0][i];
  }
  cout << anss << "\n";
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


