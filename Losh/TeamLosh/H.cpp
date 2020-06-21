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
    vec<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    map<int, int> cnt;
    set<int> ones;
    for (int i = 0; i < k; i++) {
        cnt[a[i]]++;
        if (cnt[a[i]] == 1) {
            ones.insert(a[i]);
        } else if (cnt[a[i]] == 2) {
            ones.erase(a[i]);
        }
    }
    if (ones.empty()) {
        cout << "Nothing\n";
    } else
    cout <<*ones.rbegin() << '\n';
    for (int i = k; i < n; i++) {
        cnt[a[i-k]]--;
        if (cnt[a[i-k]] == 1) {
            ones.insert(a[i-k]);
        } else if (cnt[a[i - k]] == 0){
            ones.erase(a[i - k]);
        }
        cnt[a[i]]++;
        if (cnt[a[i]] == 1) {
            ones.insert(a[i]);
        } else if (cnt[a[i]] == 2){
            ones.erase(a[i]);
        }
        if (ones.empty()) {
            cout << "Nothing\n";
        } else
            cout <<*ones.rbegin() << '\n';
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

