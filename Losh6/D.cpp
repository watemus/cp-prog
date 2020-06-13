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
constexpr ld PI = acos(-1);

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

const int MAXN = 1e6 + 10;

vec<int> g[MAXN];
int usd[MAXN];

void run() {
    int n, m;
    cin >> n >> m;
    vec<vec<int>> a(n, vec<int>(m));
    vec<pair<int, int>> coords(n * m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            coords[i * m + j] = {i, j};
        }
    }
    sort(all(coords), [&](auto &p1, auto &p2){
        return a[p1.first][p1.second] < a[p2.first][p2.second];
    });
    vec<int> mnx(n), mny(m);
    for (int i = 0; i < n; i++) {
        map<int, pair<int, int>> mp;
        for (int j = 0; j < m; j++) {
            if (mp.count(a[i][j])) {
                auto [x, y] = mp[a[i][j]];
                g[x * m + y].push_back(i * m + j);
                g[i * m + j].push_back(x * m + y);
            }
            mp[a[i][j]] = {i, j};
        }
    }
    for (int j = 0; j < m; j++) {
        map<int, pair<int, int>> mp;
        for (int i = 0; i < n; i++) {
            if (mp.count(a[i][j])) {
                auto [x, y] = mp[a[i][j]];
                g[x * m + y].push_back(i * m + j);
                g[i * m + j].push_back(x * m + y);
            }
            mp[a[i][j]] = {i, j};
        }
    }
    memset(usd, 0, sizeof usd);
    for (auto [x, y] : coords) {
        if (usd[x * m + y]) continue;
        vec<int> comp;
        int s = x * m + y;
        usd[s] = 1;
        queue<int> q;
        q.push(s);
        comp.push_back(s);
        while (q.size()) {
            int v = q.front();
            comp.push_back(v);
            q.pop();
            for (auto u : g[v]) {
                if (!usd[u]) {
                    q.push(u);
                    usd[u] = 1;
                }
            }
        }
        int ans = 1;
        for (auto v : comp) {
            ans = max({ans, mnx[v / m] + 1, mny[v % m] + 1});
        }
        for (auto v : comp) {
            mnx[v / m] = ans;
            mny[v % m] = ans;
            a[v / m][v % m] = ans;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << a[i][j] << ' ';
        }
        cout << '\n';
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

