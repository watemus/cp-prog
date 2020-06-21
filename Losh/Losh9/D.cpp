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

vec<int> nmasks, masks, p;
int ans = INFL;
int cans = 0;
int n;
bool checked = true;
vec<int> z;

void check(int i) {
    if (i == n) return;
    bool f = false;
    for (int j = 0; j < n; j++) {
        if ((nmasks[p[i]] & (1 << j)) && z[j] == 0) {
            z[j] = 1;
            check(i + 1);
            if (!checked) return;
            z[j] = 0;
            f = true;
        }
    }
    if (!f) {
        checked = false;
    }
}

void gen() {
    if (nmasks.size() < masks.size()) {
        for (int mask = 0; mask < (1 << n); mask++) {
            if ((mask & masks[nmasks.size()]) == masks[nmasks.size()]) {
                cans += __builtin_popcount(mask - masks[nmasks.size()]);
                nmasks.push_back(mask);
                gen();
                nmasks.pop_back();
                cans -= __builtin_popcount(mask - masks[nmasks.size()]);
            }
        }
    } else {
        iota(all(p), 0);
        do {
            checked = true;
            z.assign(n, 0);
            check(0);
            if (!checked) {
                return;
            }
        } while (next_permutation(all(p)));
        ans = min(cans, ans);
    }
}

void run() {
    cin >> n;
    masks.resize(n);
    p.resize(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char ch;
            cin >> ch;
            if (ch - '0') {
                masks[i] += (1 << j);
            }
        }
    }
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

