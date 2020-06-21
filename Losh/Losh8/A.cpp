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
    int n;
    cin >> n;
    string s;
    cin >> s;
    string ans = s;
    vec<int> chr[26][26];
    for (int i = n; i >= 0; i--) {
        chr[s[i] - 'a'][s[i] - 'a'].push_back(i);
    }
    for (int i = 0; i < n; i++) {
        if (ans[i] != s[i]) continue;
        bool checked = false;
        for (int st = 0; st < 26; st++) {
            if (st == s[i] - 'a') continue;
            for (int ed = 0; ed < 26; ed++) {
                if (ed == s[i] - 'a') continue;
                if (!chr[st][ed].empty()) {
                    int j = chr[st][ed].back();
                    chr[st][ed].pop_back();
                    chr[s[i] - 'a'][s[i] - 'a'].pop_back();
                    ans[i] = ans[j];
                    ans[j] = s[i];
                    chr[st][s[i] - 'a'].push_back(i);
                    chr[s[i] - 'a'][ed].push_back(j);
                    checked = true;
                    break;
                }
            }
            if (checked) break;
        }
        if (!checked) {
            cout << "Impossible\n";
            return;
        }
    }
    cout << ans << "\n";
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

