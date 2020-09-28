//
// Created by watemus on 28.09.2020.
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

inline int f(int n) {
  int ans = 1;
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      ans *= i - 1;
      n /= i;
      while (n % i == 0) {
        ans *= i;
        n /= i;
      }
    }
  }
  if (n > 1) {
    ans *= n - 1;
  }
  return ans;
}

inline int g(int n) {
  return n;
}

int F(int n, int k) {
  if (k == 1) {
    return f(n);
  } else if (n == 1) {
    return n;
  } else {
    if (k % 2) {
      return f(F(n, k - 1));
    } else {
      return F(n, k - 1);
    }
  }
}

int stup(int n, int k) {
  return F(n, k);
}

int smart(int n, int k) {
  while (k > 0 && n > 1) {
    if (k % 2) {
      n = f(n);
    }
    k--;
  }
  return n;
}

void run() {
  int n, k;
  cin >> n >> k;
  cout << smart(n, k) % (int)(100000007) << '\n';
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



