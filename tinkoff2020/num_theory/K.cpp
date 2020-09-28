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

int abs(int a) {
  if (a > 0)
    return a;
  return -a;
}

int mult(int a, int b, int mod) {
  return (__int128)a * b % mod;
}

int f(int x, int c, int mod) {
  return (mult(x, x, mod) + c) % mod;
}

const double TL = 1.7;
inline bool is_tl() {
  static int is = 0, cnt = 0;
  {
    is |= clock() > (TL - 0.1) * CLOCKS_PER_SEC;
  }
  return is;
}

int brent(int n, int x0 = 2, int c = 1) {
  int x = x0;
  int g = 1;
  int q = 1;
  int xs, y;

  int m = 128;
  int l = 1;
  while (g == 1) {
    y = x;
    for (int i = 1; i < l; i++)
      x = f(x, c, n);
    int k = 0;
    while (k < l && g == 1) {
      xs = x;
      for (int i = 0; i < m && i < l - k; i++) {
        x = f(x, c, n);
        q = mult(q, abs(y - x), n);
      }
      if (is_tl())
        return n;
      g = gcd(q, n);
      k += m;
    }
    l *= 2;
  }
  if (g == n) {
    do {
      xs = f(xs, c, n);
      if (is_tl())
        return n;
      g = gcd(abs(xs - y), n);
    } while (g == 1);
  }
  return g;
}

int pw

long long pollards_p_minus_1(long long n) {
  int B = 10;
  long long g = 1;
  vec<int> primes = {2, 3, 5, 7, 11, 13};

  while (B <= 1000000 && g < n) {
    long long a = 2 + rand() %  (n - 3);
    g = gcd(a, n);
    if (g > 1)
      return g;

    // compute a^M
    for (int p : primes) {
      if (p >= B)
        continue;
      long long p_power = 1;
      while (p_power * p <= B)
        p_power *= p;
      a = pw(a, p_power, n);

      g = gcd(a - 1, n);
      if (g > 1 && g < n)
        return g;
    }
    B *= 2;
  }
  return 1;
}



int fermat(int n, int iters = 1e6) {
  int a = ceil(sqrt(n));
  int b2 = a * a - n;
  int b = round(sqrt(b2));
  int iter = 0;
  while (b * b != b2 && iter < iters) {
    a = a + 1;
    b2 = a * a - n;
    b = round(sqrt(b2));
    iter++;
  }
  if (iter == iters && n % (a - b)) {
    return n;
  }
  return a - b;
}



void run() {
  int n;
  cin >> n;
  n--;
  vec<int> factors;
  for (int i = 2; i < 2e7; i++) {
    while (n % i == 0) {
      factors.push_back(i);
      n /= i;
    }
  }

  int cur = n;
  int dd = fermat(n, 3e8);
  cur = dd;
  n /= dd;
  while (true) {
    int d = cur;
    int pd = d;
    if (cur == 1) {
      break;
    }
    do {
      pd = d;
      d = brent(d);
      d = fermat(d);
    } while (d != pd);
    factors.push_back(d);
    cur /= d;
  }
  cur = n;
  while (true) {
    int d = cur;
    int pd = d;
    if (cur == 1) {
      break;
    }
    do {
      pd = d;
      d = brent(d, rnd() % n + 1);
      d = fermat(d);
    } while (d != pd);
    factors.push_back(d);
    cur /= d;
  }
  cout << factors.size() << '\n';
  for (auto div : factors) {
    cout << div - 1 << ' ';
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
  // cin >> t;
  while (t--) {
    run();
  }
  return 0;
}
