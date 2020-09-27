//
// Created by watemus on 19.09.2020.
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

void rec(vec<int> &primes, vec<int> &cnt, vec<int> &ans, int cur, int at, set<int> &was) {
  if (at == primes.size()) {
    if (!was.count(cur)) {
      ans.push_back(cur);
      was.insert(cur);
    }
  } else {
    cur *= primes[at];
    for (int i = 1; i <= cnt[at]; i++) {
      rec(primes, cnt, ans, cur, at + 1, was);
      cur *= primes[at];
    }
  }
}

void run() {
  int n;
  cin >> n;
  vec<int> primes, cnt;
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      cnt.push_back(0);
      primes.push_back(i);
      while (n % i == 0) {
        cnt.back()++;
        n /= i;
      }
    }
  }
  if (n > 1) {
    cnt.push_back(1);
    primes.push_back(n);
  }
  vec<int> ans;
  set<int> was;
  if (cnt.size() == 2 && cnt[0] == 1 && cnt[1] == 1) {
    cout << primes[0] << ' ' << primes[1] << ' ' << primes[1] * primes[0] << '\n';
    cout << "1\n";
    return;
  }
  if (cnt.size() == 2) {
    int cr = 1;
    for (int i = 0; i < cnt[0]; i++) {
      ans.push_back(cr * primes[0]);
      was.insert(cr * primes[0]);
      cr *= primes[0];
    }
    ans.push_back(primes[0] * primes[1]);
    was.insert(primes[0] * primes[1]);
    cr = 1;
    for (int i = 0; i < cnt[1]; i++) {
      ans.push_back(cr * primes[1]);
      was.insert(cr * primes[1]);
      cr *= primes[1];
    }
    rec(primes, cnt, ans , 1, 0, was);
    for (auto el : ans) {
      cout << el << ' ';
    }
    cout << "\n";
    cout << "0\n";
    return;
  }
  rec(primes, cnt, ans, 1, 0, was);
  for (int i = cnt.size() - 1; i >= 0; i--) {
    for (int mask = 0; mask < (1 << i); mask++) {
      vec<int> c_primes, c_cnt;
      for (int j = 0; j < i; j++) {
        if ((1 << j) & mask) {
          c_primes.push_back(primes[j]);
          c_cnt.push_back(cnt[j]);
        }
      }
      c_primes.push_back(primes[i]);
      c_cnt.push_back(cnt[i]);
      rec(c_primes, c_cnt, ans, 1, 0, was);
    }
  }
  for (auto el : ans) {
    cout << el << ' ';
  }
  cout << "\n";
  cout << "0\n";
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


