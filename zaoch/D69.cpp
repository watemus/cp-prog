//
// Created by watemus on 28.11.2020.
//

//
// Created by watemus on 25.11.2020.
//

/*
What we're dealing with here is a total lack of respect for the law
I'm the law and you can't beat the law
I'm the law and you can't beat the law
I'm the law and you can't beat the law
Fuck 'em and their law
Crack down at sundown
Fuck 'em and their law
 */

#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif

#include <bits/stdc++.h>

#ifndef KEK


const int MAX_MEM = 5e8;
int mpos = 0;
char mem[MAX_MEM];
inline void * operator new ( size_t n ) {
  char *res = mem + mpos;
  mpos += n;
  assert(mpos <= MAX_MEM);
  return (void *)res;
}
inline void operator delete ( void * ) { }

#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("vpt")

#endif


//using namespace std;

#define ALL(a) a.begin(), a.end()
#define RALL(a) a.rbegin(), a.rend()
#define FF first
#define SS second

using ll = long long;
using ld = long double;

//#define int ll

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

vec<std::pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

const int N = 1e6 + 100;
const int AL = 4;
int n, m;
std::string s, t;

namespace sa {
  const int trash = 0;
  const int root = 1;
  int to[AL][N];
  int link[N];
  int len[N];
  int at[N];
  int size = 2;
  int end = root;
  void init() {
    len[root] = 0;
    link[root] = trash;
    size = 2;
    end = root;
    for (int i = 0; i < AL; i++) {
      to[i][root] = trash;
    }
  }
  inline int new_node(int prev) {
    int v = size++;
    len[v] = len[prev] + 1;
    for (int i = 0; i < AL; i++) {
      to[i][v] = trash;
    }
    return v;
  }
  inline void push(int c) {
    int new_end = new_node(end);
    int p = end;
    while (p != trash && to[c][p] == trash) {
      to[c][p] = new_end;
      p = link[p];
    }
    if (p != trash) {
      int q = to[c][p];
      if (len[p] + 1 == len[q]) {
        link[new_end] = q;
      } else {
        int new_q = new_node(p);
        for (int i = 0; i < AL; i++) {
          to[i][new_q] = to[i][q];
        }
        link[new_q] = link[q];
        link[new_end] = link[q] = new_q;
        while (p != trash && to[c][p] == q) {
          to[c][p] = new_q;
          p = link[p];
        }
      }
    } else {
      link[new_end] = root;
    }
    end = new_end;
  }

  void make_term() {
    int cur = end;
    while (cur != root) {
      for (int i = len[link[cur]]; i < len[cur]; i++) {
        at[i] = cur;
      }
      cur = link[cur];
    }
  }

  void dbg() {
    for (int i = root; i < size; i++) {
      std::cerr << i << ": ";
      for (int j = 0; j < AL; j++) {
        std::cerr << char(j + 'a') << ": " << to[j][i] << ", ";
      }
      std::cerr << "link = " << link[i] << std::endl;
    }
  }
}

namespace suff_tree {
  struct Edge {
    int u;
    int v;
    int l;
    int r;
  };

  vec<int> adj_ids[N];
  int letter_id[AL][N];
  vec<Edge> edges;
  std::string *ss;
  int prev[N];

  inline void add_edge(int u, int v, int l, int r) {
    adj_ids[u].push_back(edges.size());
    prev[v] = edges.size();
    edges.push_back({u, v, l, r});
    int cc = 0;
    if (l >= 0) {
      cc = (*ss)[l] - 'a';
    }
    letter_id[cc][u] = edges.size() - 1;
  }

  int usd[N];

  void build(int v) {
    int cur_r = sa::len[sa::end];
    do {
      usd[v] = 1;
      int u = sa::link[v];
      int cur_l = cur_r - (sa::len[v] - sa::len[u]);
      add_edge(u, v, cur_l, cur_r);
      cur_r = cur_l;
      v = u;
    } while (v != sa::root && !usd[v]);
  }

  int deg_out[N];

  int at[N];
  int dp[N];

  void make_at(int u, int cur_len) {
    if (adj_ids[u].empty()) {
      at[cur_len] = u;
    }
    for (auto id : adj_ids[u]) {
      auto &e = edges[id];
      make_at(e.v, cur_len + (e.r - e.l));
    }
  }

  void init(std::string *ns) {
    ss = ns;
    edges.clear();
//    std::fill(adj_ids, adj_ids + sa::size, vec<int>(0));
    for (int i = 0; i < sa::size; i++) {
      adj_ids[i].clear();
    }
    for (int i = 0; i < AL; i++) {
      std::fill(letter_id[i], letter_id[i] + sa::size, -1);
    }
    std::fill(dp, dp + sa::size, 0);
    std::fill(deg_out, deg_out + sa::size, 0);
    std::fill(usd, usd + sa::size, 0);
    for (int i = sa::root + 1; i < sa::size; i++) {
      deg_out[sa::link[i]]++;
    }
    usd[sa::trash] = 1;
    for (int i = sa::root + 1; i < sa::size; i++) {
      if (deg_out[i] == 0) {
        build(i);
      }
    }
    add_edge(0, 1, -1, 0);
    make_at(1, 0);
  }

  void calc_dp(int u) {
    for (auto id : adj_ids[u]) {
      auto &e = edges[id];
      calc_dp(e.v);
      dp[u] += dp[e.v];
    }
  }

  void dbg(int u) {
    for (auto id : adj_ids[u]) {
      auto &e = edges[id];
      std::cerr << u << "->" << e.v << " (";
      for (int i = std::max(e.l, (int)0); i < e.r; i++) {
        std::cerr << (*ss)[i];
      }
      std::cerr << ")\n";
      dbg(e.v);
    }
    std::cerr << "dp[" << u << "] = " << dp[u] << std::endl;
  }

  int id;
  int pos;

  inline void tour_init() {
    id = adj_ids[0][0];
    pos = 0;
  }

  inline bool tour_check(char ch) {
    auto &e = edges[id];
    if (e.l + pos + 1 < e.r) {
      return (*ss)[e.l + pos + 1] == ch;
    } else if (letter_id[ch - 'a'][e.v] != -1){
      {
        int id2 = letter_id[ch - 'a'][e.v];
        auto &e2 = edges[id2];
        if ((*ss)[e2.l] == ch)
          return dp[e2.v] > 0;
      }
    }
    return false;
  }

  inline void tour_go(char ch) {
    auto &e = edges[id];
    if (e.l + pos + 1 < e.r) {
      pos++;
    } else if (letter_id[ch - 'a'][e.v] != -1){
      int id2 = letter_id[ch - 'a'][e.v];
      auto &e2 = edges[id2];
      if ((*ss)[e2.l] == ch) {
        pos = 0;
        id = id2;
        return;
      }
    }
  }

  inline int tour_get(char ch) {
    auto &e = edges[id];
    if (e.l + pos + 1 < e.r) {
      return e.v;
    } else if (letter_id[ch - 'a'][e.v] != -1) {
      int id2 = letter_id[ch - 'a'][e.v];
      auto &e2 = edges[id2];
      if ((*ss)[e2.l] == ch) {
        return e2.v;
      }
    }
    return 0;
  }

  inline ll tour_get() {
    return edges[id].v;
  }

  inline void tour_up() {
    if (pos == 0) {
      id = prev[edges[id].u];
      pos = edges[id].r - edges[id].l - 1;
    } else {
      pos--;
    }
  }
}

const int P1 = 5;
const int P2 = 7;
const int MOD1 = 1e9 + 7;
const int MOD2 = 1e9 + 9;

namespace hash {
  int p1[N], p2[N];
  int h1[N], h2[N];
  void init() {
    p1[0] = p2[0] = 1;
    h1[0] = h2[0] = s[0] - 'a' + 1;
    for (int i = 1; i < s.size(); i++) {
      p1[i] = p1[i - 1] * 1ll * P1 % MOD1;
      p2[i] = p2[i - 1] * 1ll * P2 % MOD2;
      h1[i] = static_cast<int>((h1[i - 1] + p1[i] * 1ll * (s[i] - 'a' + 1) % MOD1) % MOD1);
      h2[i] = static_cast<int>((h2[i - 1] + p2[i] * 1ll * (s[i] - 'a' + 1) % MOD2) % MOD2);
    }
  }
}

namespace graph {
  vec<int> adj_ids[N], g[N];

  struct Edge {
    int u;
    int v;
    ll sz_u = -1;
    ll sz_v = -1;
    Edge(int u, int v)
        : u(u), v(v) {}
  };

  vec<Edge> edges;

  void add_edge(int u, int v) {
    g[u].push_back(edges.size());
    edges.emplace_back(u, v);
    g[v].push_back(edges.size());
    edges.emplace_back(v, u);
  }

  int size[N];
  int size_c[AL][N];
  int usd[N];
  int to[N], from[N];
  int pos[N];
  int cnt = 0;
  int cnt_edges = 0;

  void find_sizes(int u, int p, int c_size) {
    from[cnt] = u;
    to[u] = cnt++;
    for (int i = 0; i < AL; i++) {
      size_c[i][u] = 0;
    }
    size[u] = 1;
    for (auto id : g[u]) {
      auto &e = edges[id];
      if (e.v != p && !usd[e.v]) {
        find_sizes(e.v, u, c_size);
        size[e.u] += size[e.v];
        edges[id].sz_v = size[e.v];
        edges[id].sz_u = c_size - size[e.v];
        edges[id ^ 1].sz_u = e.sz_v;
        edges[id ^ 1].sz_v = e.sz_u;
      }
      size_c[t[e.v] - 'a'][u] += size[e.v];
    }
  }

  void init() {
    for (int i = 1; i < n; i++) {
      int pre;
      std::cin >> pre;
      pre--;
      add_edge(i, pre);
    }
    find_sizes(0, 0, n);
    for (int i = 0; i < edges.size(); i++) {
      auto &e = edges[i];
      e.u = to[e.u];
      e.v = to[e.v];
      adj_ids[e.u].push_back(i);
    }
    std::string st = t;
    for (int i = 0; i < n; i++) {
      st[i] = t[from[i]];
    }
    t = st;
  }

  ll ans = 0;

  int d_size[N];

  void d_find_sizes(int u, int p) {
    d_size[u] = 1;
    for (auto id : adj_ids[u]) {
      auto &e = edges[id];
      if (e.v != p && !usd[e.v]) {
        d_find_sizes(e.v, u);
        d_size[u] += d_size[e.v];
      }
    }
  }

  int d_find_centroid(int u, int p, int sz) {
    for (auto id : adj_ids[u]) {
      auto &e = edges[id];
      if (e.v != p && !usd[e.v] && d_size[e.v] > sz / 2) {
        return d_find_centroid(e.v, u, sz);
      }
    }
    return u;
  }

  int depth[N];
  int q[N];
  int qs, qf;
  int prevv[N];

  int d_find_depth(int u, int p, int dep) {
    int max_depth = depth[u] = dep;
    for (auto id : adj_ids[u]) {
      auto &e = edges[id];
      if (e.v != p && !usd[e.v]) {
        max_depth = std::max(max_depth, d_find_depth(e.v, u, dep + 1));
      }
    }
    return max_depth;
  }

  int cnt_added = 0;

  int qh1[N];
  int qh2[N];

  void d_calc_pref(int u, int p, int cur_hash1, int cur_hash2, int s_len) {
    if (depth[u] > s_len) {
      return;
    }
    cur_hash1 = ((cur_hash1 * 1ll * P1) + t[u] - 'a' + 1) % MOD1;
    cur_hash2 = ((cur_hash2 * 1ll * P2) + t[u] - 'a' + 1) % MOD2;
    if (hash::h1[depth[u]] == cur_hash1 && hash::h2[depth[u]] == cur_hash2) {
      suff_tree::dp[suff_tree::at[s_len - depth[u]]]++;
      cnt_added++;
    }
    for (auto id : adj_ids[u]) {
      auto &e = edges[id];
      if (e.v != p && !usd[e.v]) {
        d_calc_pref(e.v, u, cur_hash1, cur_hash2, s_len);
      }
    }
  }

  void d_calc_ans(int u, int p, ll sign) {
    if (!suff_tree::tour_check(t[u])) {
      return;
    }
    suff_tree::tour_go(t[u]);
    ans += suff_tree::dp[suff_tree::tour_get()] * 1ll * sign;
    for (auto id : adj_ids[u]) {
      auto &e = edges[id];
      if (!usd[e.v] && e.v != p) {
        if (suff_tree::tour_check(t[e.v])) {
          d_calc_ans(e.v, u, sign);
        }
      }
      if (e.v != p) {
        for (char i = t[e.v] + 1; i < 'a' + AL - 1; i++) {
          if (suff_tree::tour_check(i)) {
            ans += suff_tree::dp[suff_tree::tour_get(i)] * 1ll * e.sz_v * sign;
          }
        }
      }
    }
    suff_tree::tour_up();
  }

  void solve(int start = 0) {
    d_find_sizes(start, start);
    int centroid = d_find_centroid(start, start, d_size[start]);
    int max_depth1 = 0;
    int max_depth2 = 0;
    depth[centroid] = 0;
    for (auto id : adj_ids[centroid]) {
      auto &e = edges[id];
      if (!usd[e.v]) {
        int cur_depth = d_find_depth(e.v, centroid, 1);
        if (cur_depth >= max_depth1) {
          max_depth2 = max_depth1;
          max_depth1 = cur_depth;
        } else if (cur_depth > max_depth2) {
          max_depth2 = cur_depth;
        }
      }
    }
    int s_len = std::min((int)s.size(), (max_depth1 + max_depth2 + 1) * 2) + 1;
    sa::init();
    sa::push(AL - 1);
    std::string cs("d");
    cs.reserve(s_len);
    for (int i = s_len - 2; i >= 0; i--) {
      sa::push(s[i] - 'a');
      cs.push_back(s[i]);
    }
    reverse(ALL(cs));
    suff_tree::init(&cs);
    cnt_added = 0;
    d_calc_pref(centroid, centroid, 0, 0, s_len);
    if (t[centroid] < s[0]) {
      ans += n;
    }
    if (cnt_added){
      suff_tree::calc_dp(0);
      suff_tree::tour_init();
//    suff_tree::dbg(0);
      d_calc_ans(centroid, centroid, 1);
      usd[centroid] = 1;
      if (suff_tree::tour_check(t[centroid]) && cnt_added) {
        for (auto id : adj_ids[centroid]) {
          auto &e = edges[id];
          if (usd[e.v]) continue;
          int max_depth = d_find_depth(e.v, centroid, 1);
          int ss_len = std::min((int) s.size(), (max_depth + 1) * 2) + 1;
          sa::init();
          sa::push(AL - 1);
          std::string ccs("d");
          ccs.reserve(ss_len);
          for (int i = ss_len - 2; i >= 0; i--) {
            sa::push(s[i] - 'a');
            ccs.push_back(s[i]);
          }
          reverse(ALL(ccs));
          suff_tree::init(&ccs);
          cnt_added = 0;
          d_calc_pref(e.v, centroid, t[centroid] - 'a' + 1, t[centroid] - 'a' + 1, ss_len);

          if (cnt_added) {
            suff_tree::calc_dp(0);
            suff_tree::tour_init();
            suff_tree::tour_go(t[centroid]);
            d_calc_ans(e.v, centroid, -1);
            for (char i = t[e.v] + 1; i < 'a' + AL - 1; i++) {
              if (suff_tree::tour_check(i)) {
                ans -= suff_tree::dp[suff_tree::tour_get(i)] * 1ll * e.sz_v;
              }
            }
          }
        }
      }
    }
    usd[centroid] = 1;
    for (auto id : adj_ids[centroid]) {
      auto &e = edges[id];
      if (!usd[e.v]) {
        solve(e.v);
      }
    }
//    suff_tree::dbg(0);
  }
}

void run() {
  std::cin >> n >> m;
//  assert(n <= 2e5);
  std::cin >> s >> t;
//  sa::init();
//
//  for (int i = s.size() - 1; i >= 0; i--) {
//    sa::push(s[i] - 'a');
//  }
//  sa::dbg();
//  suff_tree::init(s);
//  suff_tree::dbg(1);
  hash::init();
  graph::init();
  graph::solve();
  std::cout << graph::ans << '\n';
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


