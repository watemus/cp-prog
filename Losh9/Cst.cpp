//
// Created by watemus on 17.06.2020.
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


int n, sm;
vec<int> a;
vec<int> cr;
int ans = INFL;
int cs = 0;
vec<int> mn;

void gen() {
    if (cr.size() < n) {
        for (int i : {-1, 0, 1}) {
            cs += cr.back() + i;
            cr.push_back(cr.back() + i);
            mn.push_back(min(mn.back(), cr.back()));
            gen();
            mn.pop_back();
            cr.pop_back();
            cs -= cr.back() + i;
        }
    } else {
        cs += (-mn.back()) * n;
        if ((sm - cs) % n || cs > sm) {
            cs -= (-mn.back()) * n;
            return;
        }
        vec<int> ta = a;
        int zz = (sm - cs) / n;
        int cans = 0;
        for (int i = 0; i < n; i++) {
            cr[i] += -mn.back();
        }
        for (int i = 0; i < n; i++) {
            if (ta[i] < zz + cr[i]) {
                for (int d = 0; d < n; d++) {
                    if (i - d >= 0 && ta[i - d] > zz + cr[i - d]) {
                        int dt = min(ta[i - d] - (zz + cr[i - d]), (zz + cr[i]) - ta[i]);
                        cans += d * dt;
                        ta[i - d] -= dt;
                        ta[i] += dt;
                    }
                    if (i + d < n && ta[i + d] > zz + cr[i + d]) {
                        int dt = min(ta[i + d] - (zz + cr[i + d]), (zz + cr[i]) - ta[i]);
                        cans += d * dt;
                        ta[i + d] -= dt;
                        ta[i] += dt;
                    }
                }
            }
        }
        for (int i = 0; i < n; i++) {
            cr[i] += mn.back();
        }
        cs -= (-mn.back()) * n;
        ans = min(cans, ans);
    }
}

void run() {
    cin >> n;
    a.resize(n);
    sm = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sm += a[i];
    }
    reverse(all(a));
    cr.push_back(0);
    mn.push_back(0);
    gen();
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

