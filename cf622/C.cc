//
// Created by watemus on 06.06.2020.
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


vector<int> get(vector<int> &a) {
    vector<pair<int, int>> st;
    vector<int> ans(a.size());
    ans[0] = a[0];
    st.push_back({0, a[0]});
    for (int i = 1; i < a.size(); i++) {
        ans[i] = ans[i - 1];
        while (st.size() && a[i] < st.back().second) {
            int prv = -1;
            if (st.size() > 1) {
                prv = st[st.size() - 2].first;
            }
            ans[i] -= (st.back().first - prv) * st.back().second;
            st.pop_back();
        }
        int prv = -1;
        if (st.size())
            prv = st.back().first;
        ans[i] += (i - prv) * a[i];
        st.push_back({i, a[i]});
    }
    return ans;
}

void run() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> ans1 = get(a);
    reverse(all(a));
    vector<int> ans2 = get(a);
    reverse(all(a));
    int ans = 0;
    int at = 0;
    for (int i = 0; i < n; i++) {
        int cans = (ans1[i] + ans2[n - i - 1] - a[i]);
        if (cans > ans) {
            ans = cans;
            at = i;
        }
    }
    vector<int> vans(n);
    int cval = INFL;
    for (int i = at; i >= 0; i--) {
        cval = min(cval, a[i]);
        vans[i] = cval;
    }
    cval = INFL;
    for (int i = at; i < n; i++) {
        cval = min(cval, a[i]);
        vans[i] =cval;
    }
    for (auto el : vans) {
        cout << el << ' ';
    }
    cout << '\n';
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

