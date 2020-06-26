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

void chkmin(string &a, string &b) {
    if (a.size() < b.size()) return;
    if (b.size() < a.size()) {
        a = b;
        return;
    }
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == b[i]) continue;
        if (a[i] < b[i]) return;
        if (a[i] > b[i]) {
            a = b;
            return;
        }
    }
}

void run() {
    int n, k;
    cin >> n >> k;
    if (k == 0) {
        if (n % 9) {
            cout << n % 9;
        }
        for (int i = 0; i < n / 9; i++) {
            cout << 9;
        }
        cout << '\n';
        return;
    }
    bool checked = false;
    string ans(100, '9');
    for (int c = 0; c < 100; c++) {
        if (c * 9 >= n) break;
        int csum = 0;
        for (int st = 0; st <= 9; st++) {
            csum = 0;
            for (int dd = st; dd <= st + k; dd++) {
                if (dd >= 10) {
                    csum += 1 + dd - 10;
                } else {
                    csum += dd + c * 9;
                }
            }
            string cans = to_string(st);
            if (n - csum < 0 || (n - csum) % (k + 1)) continue;
            int cn = (n - csum) / (k + 1);
            for (int i = 0; i < c; i++) {
                cans.push_back('9');
            }
            if (cn < 0) continue;
            if (cn >= 9) {
                cans.push_back('8');
                cn -= 8;
            }
            while (cn >= 9) {
                cans.push_back('9');
                cn -= 9;
            }
            if (cn != 0)
                cans += to_string(cn);
            reverse(ALL(cans));
            checked = true;
            chkmin(ans, cans);
        }
    }
    if (!checked) {
        cout << "-1\n";
    } else {
        cout << ans << '\n';
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
    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}

