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
  vec<int> a(n);
  string FF = "T";
  string SS = "HL";
  int sm = 0;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    sm += a[i];
  }
  if (n == 1) {
    cout << FF << '\n';
    return;
  }
  const int MAXN = 101* 101;
  vec<int> suka(MAXN, -INFI);
  suka[0] = 0;
  for (int i = 0; i < n; i++) {
    for (int j = MAXN - 1; j >= a[i]; j--) {
      if (suka[j - a[i]] != -INFI) {
        suka[j] = max({suka[j - a[i]] + 1, suka[j]});
      }
    }
  }
  if (sm % 2 == 0 ) {
    if (suka[sm / 2] != -INFI) {
      cout << SS << '\n';
      return;
    }
    for (int i = sm / 2 + 1; i <= sm; i++) {
      if (suka[i] >= 2) {
        cout << SS << '\n';
        return;
      } else if (suka[i] == 1) {
        cout << FF << "\n";
        return;
      }
    }
    cout << FF << '\n';
  } else {
    cout << FF << '\n';
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
 