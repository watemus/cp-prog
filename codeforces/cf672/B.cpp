//
// Created by watemus on 27.09.2020.
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

[[noreturn]] void run() {
  int n;
  cin >> n;
  vec<int> a(n);
  int sm = 0;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    sm += a[i];
  }
  if (sm % n) {
    cout << "-1\n";
    return;
  }
  vec<tuple<int, int, int>> ans;
  vec<pair<int, int>> rems;
  for (int i = 1; i < n; i++) {
    if (a[i] >= (i + 1)) {
      ans.emplace_back(i, 0, a[i] / (i + 1));
      a[0] += a[i] / (i + 1) * (i + 1);
      a[i] = a[i] % (i + 1);
    }
    rems.emplace_back((i + 1 - a[i]) % (i + 1), i);
  }
  sort(ALL(rems));
  queue<int> q;
  for (auto [rem, i] : rems) {
    if (a[i] > sm / n) {
      if (a[0] >= rem) {
        if (rem != 0) {
          ans.emplace_back(0, i, rem);
          ans.emplace_back(i, 0, 1);
        }
        a[0] += a[i];
        a[i] = 0;
      } else {
        while (q.size()) {
          int j = q.front();
          q.pop();
          int jrem = (j + 1 - a[j]) % (j + 1);
          if (a[0] < jrem) {
            cout << "-1\n";
            return;
          } else {
            if (jrem != 0) {
              ans.emplace_back(0, j, jrem);
              ans.emplace_back(j, 0, 1);
              a[0] += a[j];
              a[j] = 0;
            }
          }
          if (a[0] >= rem)
            break;
        }
        if (a[0] >= rem) {
          if (rem != 0) {
            ans.emplace_back(0, i, rem);
            ans.emplace_back(i, 0, 1);
          }
          a[0] += a[i];
          a[i] = 0;
        } else {
          cout << "-1\n";
          return;
        }
      }
    } else {
      q.push(i);
    }
  }
  for (int i = 1; i < n; i++) {
    if (sm / n - a[i] != 0) {
      ans.emplace_back(0, i, sm / n - a[i]);
    }
  }
  assert(ans.size() <= 3 * n);
  cout << ans.size() << '\n';
  for (auto [i, j, x] : ans) {
    cout << i + 1 << ' ' << j + 1 << ' ' << x << '\n';
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
   cin >> t;
  while (t--) {
    run();
  }
  return 0;
}


