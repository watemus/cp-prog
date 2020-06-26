//
// Created by watemus on 13.06.2020.
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

#define int ll

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;
const ld PI = acos(-1);

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

const int MAXN = 1e5 + 20;

vec<int> g[MAXN];

int dep[MAXN], dep_mod[2];

void tree_dfs(int v, int p, int d) {
    dep_mod[dep[v] % 2]++;
    for (auto u : g[v]) {
        if (u != p) {
            dep[u] = dep[v] + 1;
            tree_dfs(u, v, d + 1);
        }
    }
}

int usd[MAXN];
vec<int> st;
int k;

void dfs(int v, int p) {
    st.push_back(v);
    usd[v] = 1;
    vec<int> was;
    for (auto u : g[v]) {
        if (usd[u] && u != p) was.push_back(u);
    }
    sort(all(was), [](int u, int v){
        return dep[u] > dep[v];
    });
    for (auto u : was) {
        {
            if (u == p) continue;
            if (dep[v] - dep[u] + 1 <= k) {
                cout << "2\n";
                cout << dep[v] - dep[u] + 1 << '\n';
                for (int i = 0; i < dep[v] - dep[u] + 1; i++) {
                    cout << st[st.size() - i - 1] + 1 << ' ';
                }
                cout << '\n';
                exit(0);
            } else {
                cout << "1\n";
                for (int i = 0; i < (k + 1) / 2; i++) {
                    cout << st[st.size() - 1 - i * 2] + 1 << ' ';
                }
                cout << '\n';
                exit(0);

            }
        }
    }
    for (auto u : g[v]) {
        if (!usd[u]) {
            dep[u] = dep[v] + 1;
            dfs(u, v);
        }
    }
    st.pop_back();
}

void run() {
    int n, m;
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    if (m == n - 1) {
        cout << "1\n";
        dep[0] = 0;
        tree_dfs(0, 0, 0);
        int cnt = 0;
        if (dep_mod[0] > dep_mod[1]) {
            for (int i = 0; i < n && cnt < (k + 1) / 2; i++) {
                if (dep[i] % 2 == 0) {
                    cout << i + 1 << ' ';
                    cnt++;
                }
            }
        } else {
            for (int i = 0; i < n && cnt < (k + 1) / 2; i++) {
                if (dep[i] % 2 == 1) {
                    cout << i + 1 << ' ';
                    cnt++;
                }
            }
        }
    } else {
        dep[0] = 0;
        dfs(0, 0);
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

