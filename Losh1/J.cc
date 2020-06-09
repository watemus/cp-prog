//
// Created by watemus on 08.06.2020.
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

const int MAXN = (1 << 19) + 228;

pair<int, int> t[MAXN * 2];

void build(int v, int lb, int rb, vec<int> &a) {
    if (rb - lb == 1) {
        t[v] = {a[lb], lb};
    } else {
        int mid = (lb + rb) / 2;
        build(v * 2 + 1, lb, mid, a);
        build(v * 2 + 2, mid, rb, a);
        if (t[v * 2 + 1].first > t[v * 2 + 2].first) {
            t[v] = t[v * 2 + 1];
        } else {
            t[v] = t[v * 2 + 2];
        }
    }
}

pair<int, int> get(int v, int lb, int rb, int ql, int qr) {
    if (qr <= lb || rb <= ql) {
        return {-1, -1};
    }
    if (ql <= lb && rb <= qr) {
        return t[v];
    }
    int mid = (lb + rb) / 2;
    auto la = get(v * 2 + 1, lb, mid, ql, qr);
    auto ra = get(v * 2 + 2, mid, rb, ql, qr);
    if (la.first == -1) return ra;
    if (ra.first == -1) return la;
    if (la.first > ra.first)
        return la;
    else
        return ra;
}

void run() {
    int n;
    cin >> n;
    vec<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build(0, 0, n, a);
    int ans = 0;
    a.push_back(INFL);
    vec<int> at(n);
    vec<pair<int, int>> st;
    st.emplace_back(-a.back(), n);
    for (int i = n - 1; i >= 0; i--) {
        while (st.size() && st.back().first >= a[i]) {
            st.pop_back();
        }
        at[i] = st.back().second;
        st.emplace_back(a[i], i);
    }
    int i = 0;
    while (i < n) {
        ans++;
        int j = at[i];
        auto [mx, ni] = get(0, 0, n, i, j);
        i = ni + 1;
    }
    cout << ans << '\n';
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

