//
// Created by watemus on 24.06.2020.
//

#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif

#include <bits/stdc++.h>

using namespace std;

#define ALL(a) a.begin(), a.end()
#define RALL(a) a.rbegin(), a.rend()
#define FF first
#define SS second

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

const int MAXN = 2e5 + 10;

int t[MAXN * 4];

void build(int v, int lb, int rb) {
    if (rb - lb == 1) {
        t[v] = INFI;
    } else {
        int mid = (lb + rb) / 2;
        build(v * 2 + 1, lb, mid);
        build(v * 2 + 2, mid, rb);
        t[v] = INFI;
    }
}

void modify(int v, int lb, int rb, int at, int new_val) {
    if (rb - lb == 1) {
        t[v] = new_val;
    } else {
        int mid = (lb + rb) / 2;
        if (at < mid) {
            modify(v * 2 + 1, lb, mid, at, new_val);
        } else {
            modify(v * 2 + 2, mid, rb, at, new_val);
        }
        t[v] = min(t[v * 2 + 1], t[v * 2 + 2]);
    }
}

void run() {
    int n, q;
    cin >> n >> q;
    build(0, 0, MAXN);
    vec<multiset<int>> a(MAXN);
    vec<int> r(n), at(n);
    for (int i = 0; i < n; i++) {
        int rating, kg;
        cin >> rating >> kg;
        a[kg].insert(rating);
        r[i] = rating;
        at[i] = kg;
        modify(0, 0, MAXN, kg, *a[kg].rbegin());
    }
    for (int i = 0; i < q; i++) {
        int id, to;
        cin >> id >> to;
        id--;
        a[at[id]].erase(a[at[id]].find(r[id]));
        if (!a[at[id]].empty())
            modify(0, 0, MAXN, at[id], *a[at[id]].rbegin());
        else
            modify(0, 0, MAXN, at[id], INFI);
        a[to].insert(r[id]);
        modify(0, 0, MAXN, to, *a[to].rbegin());
        at[id] = to;
        cout << t[0] << '\n';

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

