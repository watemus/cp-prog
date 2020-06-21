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
#define int ll

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;

void run() {
    int n;
    cin >> n;
    vector<int> st;
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        st.push_back(t);
        while (st.size() >= 2 && st[st.size() - 1] == st[st.size() - 2]) {
            int val = st.back();
            st.pop_back();
            st.pop_back();
            st.push_back(val + 1);
        }
    }
    cout << st.size() << '\n';
    for (auto el : st) {
        cout << el << ' ';
    }
}

signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#else
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#endif
    int t = 1;
//    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}