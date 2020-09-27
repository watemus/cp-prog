//
// Created by watemus on 04.08.2020.
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

#ifdef LOCAL
#else
#endif

vec<int> build_suffix_array(string &s) {
  int n = s.size();
  vec<int> sa(n);
  iota(ALL(sa), 0);
  sort(ALL(sa), [&](int idx1, int idx2){
    return s[idx1] < s[idx2];
  });
  vec<int> c(n);
  c[sa[0]] = 0;
  for (int i = 1; i < n; i++) {
    c[sa[i]] = c[sa[i - 1]];
    if (s[sa[i - 1]] != s[sa[i]]) {
      c[sa[i]]++;
    }
  }
  for (int k = 0; (1 << k) < n; k++) {
    for (int i = 0; i < n; i++) {
      sa[i] = (sa[i] - (1 << k) + n) % n;
    }
    vec<int> cnt(n), pos(n);
    for (int i = 0; i < n; i++) {
      cnt[c[i]]++;
    }
    for (int i = 1; i < n; i++) {
      pos[i] = pos[i - 1] + cnt[i - 1];
    }
    vec<int> new_sa(n);
    for (int i = 0; i < n; i++) {
      new_sa[pos[c[sa[i]]]] = sa[i];
      pos[c[sa[i]]]++;
    }
    sa = new_sa;
    vec<int> new_c(n);
    for (int i = 1; i < n; i++) {
      new_c[sa[i]] = new_c[sa[i - 1]];
      if (tie(c[sa[i]], c[(sa[i] + (1 << k)) % n]) != tie(c[sa[i - 1]], c[(sa[i - 1] + (1 << k)) % n])) {
        new_c[sa[i]]++;
      }
    }
    c = new_c;
  }
  return sa;
}

int check(string &t, string &s, int at) {
  for (int i = at; i < at + s.size(); i++) {
    if (t[i] != s[i - at])
      return t[i] - s[i - at];
  }
  return 0;
}

int find_left(string &t, string &s, vec<int> &sa) {
  int lb = -1;
  int rb = t.size() - 1;
  while (lb + 1 < rb) {
    int mid = (lb + rb) / 2;
    int checked = check(t, s, sa[mid]);
    if (checked >= 0) {
      rb = mid;
    } else {
      lb = mid;
    }
  }
  return rb;
}

int find_right(string &t, string &s, vec<int> &sa) {
  int lb = 0;
  int rb = t.size();
  while (lb + 1 < rb) {
    int mid = (lb + rb) / 2;
    int checked = check(t, s, sa[mid]);
    if (checked <= 0) {
      lb = mid;
    } else {
      rb = mid;
    }
  }
  return lb;
}

void run() {
  string t;
  cin >> t;
  auto rt = t;
  reverse(ALL(rt));
  t.push_back('$');
  auto sa_t = build_suffix_array(t);
  rt.push_back('$');
  auto sa_rt = build_suffix_array(rt);
  vec<int> cnt_in(t.size()), cnt_out(t.size());
  vec<int> begs_in(t.size()), ends_in(t.size());
  vec<int> begs_out(t.size()), ends_out(t.size());
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    int lb = find_left(t, s, sa_t);
    int rb = find_right(t, s, sa_t);
    if (check(t, s, sa_t[lb]) != 0) continue;
    begs_in[lb]++;
    ends_in[rb]++;
    reverse(ALL(s));
    lb = find_left(rt, s, sa_rt);
    rb = find_right(rt, s, sa_rt);
    begs_out[lb]++;
    ends_out[rb]++;
  }
  int covered_in = 0, covered_out = 0;
  for (int i = 0; i < t.size(); i++) {
    covered_in += begs_in[i];
    covered_out += begs_out[i];
    cnt_in[sa_t[i]] = covered_in;
    cnt_out[t.size() - sa_rt[i] - 1] = covered_out;
    covered_in -= ends_in[i];
    covered_out -= ends_out[i];
  }
  int ans = 0;
  for (int i = 0; i < t.size(); i++) {
    ans += cnt_out[i] * cnt_in[i];
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
  //cin >> t;
  while (t--) {
    run();
  }
  return 0;
}


