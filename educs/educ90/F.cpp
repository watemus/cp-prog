//
// Created by watemus on 25.06.2020.
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

void run() {
    int n;
    cin >> n;
    vec<int> a(n);
    multiset<int> b;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        int el;
        cin >> el;
        b.insert(el);
    }
    vec<int> vmn(n);
    int mn = *b.begin();
    int mx = *b.rbegin();
    for (int i = 0; i < n; i++) {
        auto it = b.lower_bound(a[i] - mx);
        if (it == b.end()) {
            cout << "NO\n";
            return;
        }
        vmn[i] = *it;
    }
    int st = -1;
    for (int i = 0; i < n; i++) {
        if (vmn[i] == mn && vmn[(i + 1) % n] == mn) {
            st = i;
            break;
        }
    }
    if (st == -1) {
        cout << "NO\n";
        return;
    }
    b.erase(b.find(mn));
    vec<int> ans(n);
    ans[st] = mn;
    for (int i = st + 1; i < st + n; i++) {
        auto it = b.lower_bound(a[i % n] - ans[(i - 1 + n) % n]);
        if (it == b.end()) {
            cout << "NO\n";
            return;
        }
        ans[i % n] = *it;
        b.erase(it);
    }
    cout << "YES\n";
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
   cin >> t;
    while (t--) {
        run();
    }
    return 0;
}

