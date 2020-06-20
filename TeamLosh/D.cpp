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

//#define int ll

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;
const ld PI = acos(-1);

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif
const int MAX = 1e6;
const int MAXN = 300;

set<int> g[MAXN];
int mt[MAX];
int usd[MAXN];

bool find_matching(int v) {
    if (usd[v])  return false;
    usd[v] = true;
    for (auto u : g[v]) {
        if (mt[u] == -1 || find_matching(mt[u])) {
            mt[u] = v;
            return true;
        }
    }
    return false;
}

void run() {
    int n;
    cin >> n;
    int cnt_v = 0;
    map<int, string> v2s;
    map<string, int> s2v;
    string cr;
    for (char ch = 'a'; ch <= 'z'; ch++) {
        cr.push_back(ch);
        s2v[cr] = cnt_v;
        v2s[cnt_v] = cr;
        cnt_v++;
        for (char th = 'a'; th <= 'z'; th++) {
            cr.push_back(th);
            s2v[cr] = cnt_v;
            v2s[cnt_v] = cr;
            cnt_v++;
            for (char zh = 'a'; zh <= 'z'; zh++) {
                cr.push_back(zh);
                s2v[cr] = cnt_v;
                v2s[cnt_v] = cr;
                cnt_v++;
                for (char xh = 'a'; xh <= 'z'; xh++) {
                    cr.push_back(xh);
                    s2v[cr] = cnt_v;
                    v2s[cnt_v] = cr;
                    cnt_v++;
                    cr.pop_back();
                }
                cr.pop_back();
            }
            cr.pop_back();
        }
        cr.pop_back();
    }
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int mask = 1; mask < (1 << s.size()); mask++) {
            if (__builtin_popcount(mask) > 4) continue;
            string t;
            for (int j = 0; j < s.size(); j++) {
                if (mask & (1 << j)) {
                    t.push_back(s[j]);
                }
            }
            g[i].insert(s2v[t]);
        }
    }
    memset(mt, -1, sizeof mt);
    for (int i = 0; i < n; i++) {
        memset(usd, 0, sizeof usd);
        find_matching(i);
    }
    int cc = 0;
    vec<string> ans(n);
    for (int i = 0; i < MAX; i++) {
        if (mt[i] != -1) {
            ans[mt[i]] = v2s[i];
            cc++;
        }
    }
    if (cc != n) {
        cout << "-1\n";
    } else {
        for (auto &s : ans) {
            cout << s << '\n';
        }
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
    std::freopen("input.txt", "r", stdin);
    std::freopen("output.txt", "w", stdout);
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

