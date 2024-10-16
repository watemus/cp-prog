#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif
#include <bits/stdc++.h>

using namespace std;

#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define ff first
#define ss second

using ll = long long;
using ld = long double;
//#define int ll

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;
const int AL = 26 + 1;
const int MIN_EL = 'a';

const int sa_trash = 0;
const int sa_root = 1;

#ifdef LOCAL
constexpr int SA_SIZE = 30;
#else
constexpr int SA_SIZE = 2'000'000;
#endif

struct Suffix_automaton {
  int to[AL][SA_SIZE];
  int len[SA_SIZE];
  int link[SA_SIZE];
  int size = 2;
  int end = sa_root;
  Suffix_automaton() {
    fill(len, len + SA_SIZE, 0);
    fill(link, link + SA_SIZE, sa_trash);
    for (auto &to_i : to) {
      memset(to_i, sa_trash, sizeof to_i);
    }
  }
  int push(char ch, int last) {
    int cur = new_node(last);
    int p = last;
    while (p != sa_trash && to[ch - MIN_EL][p] == sa_trash) {
      to[ch - MIN_EL][p] = cur;
      p = link[p];
    }
    if (p != sa_trash) {
      int q = to[ch - MIN_EL][p];
      if (len[p] + 1 == len[q]) {
        link[cur] = q;
      } else {
        int nw = cpy_node(q);
        len[nw] = len[p] + 1;
        link[q] = link[cur] = nw;
        while (p != sa_trash && to[ch - MIN_EL][p] == q) {
          to[ch - MIN_EL][p] = nw;
          p = link[p];
        }
      }
    } else {
      link[cur] = sa_root;
    }
    return cur;
  }
  inline int new_node(int p) {
    len[size] = len[p] + 1;
    return size++;
  }
  inline int cpy_node(int u) {
    int v = new_node(u);
    for (auto &to_i : to) {
      to_i[v] = to_i[u];
    }
    link[v] = link[u];
    return v;
  }
  void add_string(string &s) {
    int cur = end;
    for (auto ch : s) {
      end = push(ch, end);
    }
    //end = push(MIN_EL + AL - 1, cur);
  }
  bool check(string &s) {
    int cur = sa_root;
    for (auto &ch : s) {
      cur = to[ch - MIN_EL][cur];
    }
    return cur != sa_trash;
  }
};


void run() {
  string q;
  Suffix_automaton sa;
  while (cin >> q) {
    if (q == "A") {
      string s;
      cin >> s;
      for (auto &ch : s) {
        ch = tolower(ch);
      }
      sa.add_string(s);
    } else {
      string s;
      cin >> s;
      for (auto &ch : s) {
        ch = tolower(ch);
      }
      cout << (sa.check(s) ? "YES\n" : "NO\n");
    }
  }
}

signed main() {
#ifdef LOCAL
  freopen("input.txt", "r", stdin);
#else
  ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#endif
  int t = 1;
//    cin >> t;
  while (t--) {
    run();
  }
  return 0;
}