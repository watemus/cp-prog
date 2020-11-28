//
// Created by watemus on 14.11.2020.
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

using ftype = complex<long double>;

vec<ftype> get_num(string &s) {
  vec<ftype> num;
  for (int i = s.size() - 1; i >= (s[0] == '-'); i--) {
    num.emplace_back(s[i] - '0');
  }
  while (__builtin_popcount(num.size()) != 1) {
    num.emplace_back(0);
  }
  return num;
}

void fft(vec<ftype> &s, vec<ftype> &ans, int n, ftype t, int a, int b, int c) {
  if (n == 1) {
    ans[c] = s[a];
  } else {
    fft(s, ans, n / 2, t * t, a, b * 2, c);
    fft(s, ans, n / 2, t * t, a + b, b * 2, c + n / 2);
    ftype x = 1;
    for (int i = 0; i < n / 2; i++) {
      ftype an1 = ans[c + i];
      ftype an2 = ans[c + i + n / 2];
      ans[c + i] = an1 + x * an2;
      ans[c + i + n / 2] = an1 - x * an2;
      x *= t;
    }
  }
}

void run() {
  string s, t;
  cin >> s >> t;
  int sign = ((s[0] == '-' ? -1 : 1)) * ((t[0] == '-' ? -1 : 1));
  auto a = get_num(s);
  auto b = get_num(t);
  while (a.size() < b.size()) a.emplace_back(0);
  while (b.size() < a.size()) b.emplace_back(0);
  int n = a.size();
  for (int i = 0; i < n; i++) {
    a.emplace_back(0);
    b.emplace_back(0);
  }
  n *= 2;
  vec<ftype> ans_a(n), ans_b(n);
  fft(a, ans_a, n, ftype(cos(2 * PI / n), sin(2 * PI / n)), 0, 1, 0);
  fft(b, ans_b, n, ftype(cos(2 * PI / n), sin(2 * PI / n)), 0, 1, 0);
  for (int i = 0; i < n; i++) {
    ans_a[i] *= ans_b[i];
  }
  vec<ftype> ans(n);
  fft(ans_a, ans, n, ftype(cos(-2 * PI / n), sin(-2 * PI / n)), 0, 1, 0);
  int carry = 0;
  for (int i = 0; i < n; i++) {
    ans[i] /= n;
    int cr = round(ans[i].real());
    cr += carry;
    ans[i] = cr % 10;
    carry = cr / 10;
  }
  string sans;
  for (int i = 0; i < n; i++) {
    sans.push_back(int(round(ans[i].real())) + '0');
  }
  while (sans.size() > 1 && sans.back() == '0')
    sans.pop_back();
  reverse(ALL(sans));
  if (sign == -1 && sans != "0") {
    cout << '-';
  }
  cout << sans << '\n';
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


