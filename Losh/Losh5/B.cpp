//
// Created by watemus on 12.06.2020.
//
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

template<typename T>
using vec = vector<T>;

template<typename T>
using uset = unordered_set<T>;

template<typename T1, typename T2>
using umap = unordered_map<T1, T2>;

//#define int ll

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;
constexpr ld PI = acos(-1);

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

const int MAXN = 1e6 + 10;
const int MAXC = 26;

int trie[MAXC][MAXN];
int cnt_str[MAXN];
int is_end[MAXN];
int cnt_v = 1;

void add_str(string &str) {
    int v = 0;
    cnt_str[v]++;
    for (auto ch : str) {
        if (trie[ch - 'a'][v] == -1) {
            trie[ch - 'a'][v] = cnt_v++;
        }
        v = trie[ch - 'a'][v];
        cnt_str[v]++;
    }
    is_end[v] = 1;
}

int usd[MAXC];
int g[MAXC][MAXC];
string top_sort;

bool dfs(int v) {
    usd[v] = 1;
    for (int u = 0; u < MAXC; u++) {
        if (g[v][u]) {
            if (usd[u] == 1) {
                return true;
            }
            if (!usd[u]) {
                bool cyclic = dfs(u);
                if (cyclic)
                    return true;
            }
        }
    }
    usd[v] = 2;
    top_sort.push_back(v + 'a');
    return false;
}

void make_ans(string &str) {
    top_sort.clear();
    memset(usd, 0, sizeof usd);
    for (int i = 0; i < MAXC; i++) {
        memset(g[i], 0, sizeof g[i]);
    }
    int v = 0;
    for (auto ch : str) {
        int to = ch - 'a';
        if (is_end[v]) {
            cout << "nemoguce\n";
            return;
        }
        for (int i = 0; i < MAXC; i++) {
            if (i == to) continue;
            if (trie[i][v] != -1) {
                g[to][i] = 1;
            }
        }
        v = trie[to][v];
    }
    for (int i = 0; i < MAXC; i++) {
        if (!usd[i]) {
            bool cyclic = dfs(i);
            if (cyclic) {
                cout << "nemoguce\n";
                return;
            }
        }
    }
    reverse(all(top_sort));
    cout << top_sort << '\n';
}

void run() {
    for (int i = 0; i < MAXC; i++) {
        memset(trie[i], -1, sizeof trie[i]);
    }
    int n;
    cin >> n;
    vec<string> s(n);
    for (auto &str : s) {
        cin >> str;
        add_str(str);
    }
    for (auto &str : s) {
        make_ans(str);
    }
}
/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
*/

signed main() {
#ifdef LOCAL
    std::freopen("input.txt", "r", stdin);
#else
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
#endif
    cout << fixed << setprecision(20);
    int t = 1;
//    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}


