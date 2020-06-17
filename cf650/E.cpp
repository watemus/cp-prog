//
// Created by watemus on 16.06.2020.
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

void run() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    int ans = 1;
    for (int i = 2; i <= k; i++) {
        if (k % i == 0 && i <= n) {
            ans = i;
        }
    }
    if (n < k) {
        cout << ans << '\n';
        return;
    }
    map<char, int> cnt;
    for (auto ch : s) {
        cnt[ch]++;
    }
    int lb = 0;
    int rb = n + 1;
    while (lb + 1 < rb) {
        int mid = (lb + rb) / 2;
        priority_queue<int> pq;
        for (auto [k, v] : cnt) pq.push(v);
        for (int i = 0; i < k; i++) {
            if (pq.top() < mid) {
                rb = mid;
                break;
            } else {
                int tp = pq.top();
                pq.pop();
                tp -= mid;
                pq.push(tp);
            }
        }
        if (rb != mid) lb = mid;
    }
    cout << max(ans, lb * k) << '\n';
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

