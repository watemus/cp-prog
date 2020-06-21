//
// Created by watemus on 20.06.2020.
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
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

vec<vec<int>> g;

pair<int, int> ask(vec<int> &v) {
    cout << "? " << v.size() << ' ';
    for (auto u : v) {
        cout << u + 1 << ' ';
    }
    cout << endl;
    int u;
    cin >> u;
    u--;
    int d;
    cin >> d;
    return {u, d};
}

vec<int> fnd;

void dfs(int v, int p, int d, int td) {
    if (d == td) {
        fnd.push_back(v);
        return;
    }
    for (auto u : g[v]) {
        if (u != p) {
            dfs(u, v, d + 1, td);
        }
    }
}

void run() {
    int n;
    cin >> n;
    g.assign(n, {});
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vec<int> al(n);
    iota(all(al), 0);
    auto [root, len] = ask(al);
    int lb = max(0LL, len / 2 - 2);
    int rb = len + 1;
    int one = -1;
    while (lb + 1 < rb) {
        int mid = (lb + rb) / 2;
        fnd.clear();
        dfs(root, -1, 0, mid);
        if (fnd.size() == 0) {
            rb = mid;
            continue;
        }
        auto [cv, clen] = ask(fnd);
        if (clen > len) {
            rb = mid;
        } else {
            lb = mid;
            one = cv;
        }
    }
    fnd.clear();
    dfs(one, -1, 0, len);
    auto [scd, dd] = ask(fnd);
    cout << "! " << one + 1 << " " << scd + 1 << endl;
    string s;
    cin >> s;
    if (s == "Incorrect")
        exit(0);
}
/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
*/

signed main() {
#ifdef LOCAL
    //std::freopen("input.txt", "r", stdin);
#else
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
#endif
    cout << fixed << setprecision(20);
    int t = 1;
    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}

