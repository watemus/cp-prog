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
    vector<int> p(n), c(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
    }
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    vector<int> usd(n);
    int ans = INFL;
    for (int i = 0; i < n; i++) {
        if (!usd[i]) {
            vector<int> cycle;
            int j = i;
            while (!usd[j]) {
                cycle.push_back(j);
                usd[j] = 1;
                j = p[j];
            }
            for (int k = 1; k <= cycle.size(); k++) {
                if (cycle.size() % k) continue;
                for (int start = 0; start < k; start++) {
                    bool checked = false;
                    for (int cur = start + k; cur < cycle.size(); cur += k) {
                        if (c[cycle[cur]] != c[cycle[cur - k]]) {
                            checked = true;
                            break;
                        }
                    }
                    if (!checked) {
                        ans = min(ans, k);
                        break;
                    }
                }
            }
        }
    }
    cout << ans << '\n';
}

signed main() {
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#else
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#endif
    int t = 1;
    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}