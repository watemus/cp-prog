//
// Created by watemus on 12.09.2020.
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


void run() {
  int n;
  cin >> n;
  int target =  99874;
  int miters = 10000;
  int iters = 0;
  vec<int> st(n + 1, 1);
  auto ask = [&](int k) {
    iters++;
    assert(iters <= miters);
    assert(k <= n);
#ifdef LOCAL
    int ans = 0;
    for (int i = k; i <= n; i += k) {
      ans += st[i];
    }
    return ans;
#else
    cout << "A " << k << endl;
    int ans;
    cin >> ans;
    return ans;
#endif
  };
  auto rem = [&](int k) {
    iters++;
    assert(k <= n);
    assert(iters <= miters);
#ifdef LOCAL
    int ans = 0;
    for (int i = k; i <= n; i += k) {
      ans += st[i];
      if (i == target)
        continue;
      st[i] = 0;
    }
    return ans;
#else
    cout << "B " << k << endl;
    int ans;
    cin >> ans;
    return ans;
#endif
  };

  auto make_ans = [&](int k) {
#ifdef LOCAL
    cout << iters + 1 << ' ' << k <<  endl;
    assert(iters <= miters);
#else
    cout << "C " << k << endl;
#endif
    exit(0);
  };
  if (n == 1) {
    make_ans(1);
  }
  vec<int> primes;
  vec<int> sieve(n + 1);
  for (int i = 2; i <= n; i++) {
    if (!sieve[i]) {
      primes.push_back(i);
      for (int j = i * i; j <= n; j+=i) {
        sieve[j] = 1;
      }
    }
  }
  int S = sqrt(n);
  int i = 0;
  int ans = 1;
  for (i = 0; primes[i] <= S; i++) {
    int t1 = rem(primes[i]);
    int t2 = rem(primes[i]);
    while (t2 != 0) {
      ans *= primes[i];
      if (ans * primes[i] > n)
        break;
      t2 = rem(ans * primes[i]);
    }
  }
  int lb = i;
  int rb = primes.size();
  while (lb + 1 < rb) {
    int mid = (lb + rb) / 2;
    int cnt = 0;
    int cr = ask(1);
    for (i = lb; i < mid; i++) {
      {
        cnt += rem(primes[i]);
      }
    }
    cr -= cnt;
    if (cr != ask(1)) {
      for (i = lb; i < mid; i++) {
        if (primes[i] * ans <= n && ask(primes[i] * ans)) {
          make_ans(ans * primes[i]);
        }
      }
    } else {
      lb = mid;
    }
  }
  if (ans * primes[lb] <= n) {
  rem(ans * primes[lb]);
  if (rem(ans * primes[lb])) {
    make_ans(ans * primes[lb]);
  }}
  {
    make_ans(ans);
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
  //cin >> t;
  while (t--) {
    run();
  }
  return 0;
}


