//
// Created by watemus on 04.06.2020.
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
//#define int ll

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;
constexpr ld PI = acos(-1);

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

constexpr int MAXN = 21;

vector<pair<int, int>> graph_govna[1 << MAXN];
int sukablyad[1 << MAXN];

void run() {
    int n, m;
    cin >> n;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    int maska_govna = 0;
    for (int i = 0; i < MAXN; i++) {
        maska_govna += (1 << i);
    }
    vector<int> deg(1 << MAXN);
    for (int otvet_govna = MAXN - 1; otvet_govna >= 0; otvet_govna--) {
        deg.assign(1 << otvet_govna, 0);
        fill(graph_govna, graph_govna + (1 << otvet_govna), vector<pair<int, int>>());
        maska_govna -= (1 << otvet_govna);
        int start = 0;
        multimap<pair<int, int>, pair<int, int>> all;
        for (int i = 0; i < n; i++) {
            auto [x, y] = a[i];
            graph_govna[x & maska_govna].emplace_back(i, y & maska_govna);
            graph_govna[y & maska_govna].emplace_back(i, x & maska_govna);
            deg[x & maska_govna]++;
            deg[y & maska_govna]++;
            start = x & maska_govna;
        }
        bool correct = true;
        for (auto el : deg) {
            if (el % 2) {
                correct = false;
                break;
            }
        }
        if (!correct)
            continue;
        memset(sukablyad, 0, sizeof sukablyad);
        vector<int> euler_govna;
        vector<int> st;
        st.push_back(start);
        while (st.size()) {
            int v = st.back();
            bool found = false;
            while (graph_govna[v].size()) {
                if (!sukablyad[graph_govna[v].back().first]) {
                    sukablyad[graph_govna[v].back().first] = 1;
                    st.push_back(graph_govna[v].back().second);
                    graph_govna[v].pop_back();
                    found = true;
                    break;
                } else {
                    graph_govna[v].pop_back();
                }
            }
            if (!found) {
                st.pop_back();
                euler_govna.push_back(v);
            }
        }
        if (euler_govna.size() != n + 1) {
            continue;
        }
        for (int i = 0; i < n; i++) {
            auto [x, y] = a[i];
            all.insert({{x&maska_govna, y&maska_govna}, {2 * i, 2 * i + 1}});
            all.insert({{y&maska_govna, x&maska_govna}, {2 * i + 1, 2 * i}});
        }
        cout << otvet_govna << '\n';
        set<int> sukablyad2;
        for (int i = 0; i < n; i++) {
            auto fnd = all.find({euler_govna[i], euler_govna[i + 1]});
            while (sukablyad2.count(fnd->second.first) || sukablyad2.count(fnd->second.second)) {
                all.erase(fnd);
                fnd = all.find({euler_govna[i], euler_govna[i + 1]});
            }
            sukablyad2.insert(fnd->second.first);
            sukablyad2.insert(fnd->second.second);
            cout << fnd->second.first + 1<< ' ' << fnd->second.second + 1<< ' ';

        }
        return;
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

