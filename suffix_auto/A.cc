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
const int AL = 12;
const int MIN_EL = 0;

const int sa_trash = 0;
const int sa_root = 1;

#ifdef LOCAL
constexpr int SA_SIZE = 30;
#else
constexpr int SA_SIZE = 2'000'000;
#endif

struct Suffix_automaton {
    int to[AL][SA_SIZE];
    ll len[SA_SIZE];
    int link[SA_SIZE];
    ll dp[SA_SIZE];
    int size = 2;
    int end = sa_root;
    bool term[SA_SIZE];
    int qq[SA_SIZE];
    int prev[SA_SIZE];
    int ans_v = sa_root;
    int prev_ch[SA_SIZE];
    ll ans = 0;
    Suffix_automaton() {
        fill(len, len + SA_SIZE, 0);
        fill(link, link + SA_SIZE, sa_trash);
        fill(dp, dp + SA_SIZE, -1);
        memset(term, 0, sizeof term);
        for (auto &to_i : to) {
            memset(to_i, sa_trash, sizeof to_i);
        }
    }
    int push(int ch, int last) {
        int cur = new_node(last, ch);
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
                int nw = cpy_node(q, ch);
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
    inline int new_node(int p, int ch) {
        len[size] = len[p] + 1;
        prev[size] = p;
        prev_ch[size] = ch;
        return size++;
    }
    inline int cpy_node(int u, int ch) {
        int v = new_node(u, ch);
        for (auto &to_i : to) {
            to_i[v] = to_i[u];
        }
        link[v] = link[u];
        return v;
    }
    void add_string(vector<int> &s) {
        int cur = end;
        for (auto ch : s) {
            end = push(ch, end);
            cur = end;
        }
        while (cur != sa_root) {
            term[cur] = true;
            cur = link[cur];
        }
        //end = push(MIN_EL + AL - 1, cur);
    }
    bool check(vector<int> &s) {
        int cur = sa_root;
        for (auto &ch : s) {
            cur = to[ch - MIN_EL][cur];
        }
        return cur != sa_trash;
    }
    int calc_dp(int v) {
        if (dp[v] != -1) {
            return dp[v];
        }
        if (term[v]) {
            dp[v] = 1;
        } else {
            dp[v] = 0;
        }
        for (auto &to_i : to) {
            if (to_i[v] != sa_trash) {
                dp[v] += calc_dp(to_i[v]);
            }
        }
        if (dp[v] * len[v] >= ans) {
            ans = dp[v] * len[v];
            ans_v = v;
        }
        return dp[v];
    }
    void print_refren() {
        cout << ans << '\n';
        vector<int> ans;
        int cur = ans_v;
        while (cur != sa_root) {
            ans.push_back(prev_ch[cur]);
            cur = prev[cur];
        }
        reverse(all(ans));
        cout << ans.size() << '\n';
        for (auto &el : ans) {
            cout << el << ' ';
        }
        cout << '\n';
    }
};


void run() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    Suffix_automaton sa;
    sa.add_string(a);
    sa.calc_dp(sa_root);
    sa.print_refren();
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