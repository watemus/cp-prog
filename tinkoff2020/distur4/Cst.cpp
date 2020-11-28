//
// Created by watemus on 29.10.2020.
//

//
// Created by watemus on 29.10.2020.
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

const int N = 5001;

int a[N];
int kth[N];

void run() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    a[i] += i;
    cout << a[i] << ' ';
  }
  cout << endl;
  memcpy(kth, a, sizeof a);
  nth_element(kth, kth + n / 2, kth + n);
  kth[n / 2] = max(kth[n / 2], n);
  int ans = INFL;
  int cans = 0;
  for (int i = 0; i < n; i++) {
    if (a[i] < kth[n / 2]) cans += kth[n / 2] - a[i];
    else cans += a[i] - kth[n / 2];
  }
  ans = min(ans, cans);
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < i; j++) {
      ++a[j];
    }
    for (int j = i; j < n; j++) {
      --a[j];
    }
    memcpy(kth, a, sizeof a);
    nth_element(kth, kth + n / 2, kth + n);
    kth[n / 2] = max({kth[n / 2], i + 1, n - i});
    cans = 0;
    for (int i = 0; i < n; i++) {
      if (a[i] < kth[n / 2]) cans += kth[n / 2] - a[i];
      else cans += a[i] - kth[n / 2];
    }
    ans = min(ans, cans);
  }
  cout << ans << '\n';
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
