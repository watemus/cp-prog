//
// Created by watemus on 19.06.2020.
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

const int MAXN = 2e5;

vec<int> g[MAXN];

void run() {
    int n, m;
    cin >> n >> m;
    vec<int> cnt(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[v].push_back(u);
        cnt[u]++;
    }
    priority_queue<int> q;
    for (int i = 0; i < n; i++) {
        if (cnt[i] == 0) q.push(i);
    }
    vec<int> ap(n);
    for (int i = n - 1; i >= 0; i--) {
        int v = q.top();
        ap[v] = i + 1;
        q.pop();
        for (auto u : g[v]) {
            cnt[u]--;
            if (cnt[u] == 0) q.push(u);
        }
    }
    for (int i = 0; i < n; i++) {
        cout << ap[i] << ' ';
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

