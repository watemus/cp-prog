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
//
constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;
const int AL = 30;
const int MIN_EL = 0;

const int sa_trash = 0;
const int sa_root = 1;
#ifdef LOCAL
constexpr int SA_SIZE = 30;
#else
constexpr int SA_SIZE = 2'00'100;
#endif


struct Suffix_automaton {
    int size = 2;
    int end = sa_root;
    int prev[SA_SIZE];
    int to[AL][SA_SIZE];
    set<int> has[SA_SIZE];
    ll len[SA_SIZE];
    int link[SA_SIZE];
    bool term[SA_SIZE];
    int ans_v = sa_root;
    int prev_ch[SA_SIZE];
    ll ans = 0;
    Suffix_automaton() {
        fill(len, len + SA_SIZE, 0);
        fill(link, link + SA_SIZE, sa_trash);
        fill(has, has + SA_SIZE, set<int>());
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
            has[p].insert(ch);
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
                prev[nw] = p;
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
        has[v] = has[u];
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
    bool calc_ans(int v, int ln, int pst, int n) {
        if (ln == n) {
            ans += pst;
            return true;
        }
        bool fnd = false;
        for (auto u : has[v]) {
            bool chk = calc_ans(to[u][v], ln + 1, pst, n);
            if (chk) {
                fnd = true;
                pst = ln;
            }
        }
        return fnd;
    }
};


void run() {
    string s = "teoreticheskiyzachet";
    vector<int> a;
    for (auto ch : s) {
        a.push_back(ch - 'a');
    }
    Suffix_automaton sa;
    sa.add_string(a);
    int cnt = 0;
    for (int i = 0; i < AL; i++) {
        cnt += sa.to[i][sa_root] != sa_trash;
    }
    cout << cnt << endl;
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