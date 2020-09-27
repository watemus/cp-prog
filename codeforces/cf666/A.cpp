//
// Created by watemus on 30.08.2020.
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

void run() {
  int n;
  cin >> n;
  vec<int> a(n), b(n), z(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    int aa =abs(a[i]);
    z[i] = n - (aa % n + n) % n;
    b[i] = aa / n + 1 - z[i];
  }
  if (n == 1) {
    cout << "1 1\n1\n1 1\n1\n";
    cout << "1 1\n";
    cout << -a[0] - 2 << '\n';
    return;
  }
  cout << "1 " << n << '\n';
  for (int i = 0; i < n; i++) {
    if (a[i] > 0) {
      cout << -n * b[i] << ' ';
      a[i] -= n * b[i];
    } else {
      cout << n * b[i] << ' ';
      a[i] += n * b[i];
    }
  }
  cout << '\n';
  cout << "2 " << n << '\n';
  for (int i = 1; i < n; i++) {
    if (a[i] > 0) {
      cout << -z[i] * (n - 1) << ' ';
    }else {
      cout << z[i] * (n - 1) << ' ';

    }
  }
  cout << "\n1 1\n";
  cout << -a[0] << '\n';
}

signed main() {
#ifdef LOCAL
  std::freopen("input.txt", "r", stdin);
#else
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
#endif
  int t = 1;
  // >> t;
  while (t--) {
    run();
  }
  return 0;
}


