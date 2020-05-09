//
// Created by watemus on 01.05.2020.
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
#define int ll

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;

#ifdef LOCAL
#else
#endif


void run() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    vector<string> ans(k);
    map<char, int> cnt;
    int sm = s.size();
    for (int ch = 'a'; ch <= 'z'; ch++) cnt[ch] = 0;
    for (auto ch : s) cnt[ch]++;
    char ch = 'a';
    {
        while (ch <= 'z' && cnt[ch] == 0) ch++;
        if (cnt[ch] == sm) {
            for (int i = 0; i < (n + k - 1) / k; i++) {
                cout << ch;
            }
            cout << '\n';
        } else {
            while (1) {
                bool f = false;
                for (int i = 0; i < k; i++) {
                    while (!cnt[ch] && ch <= 'z') ch++;
                    if (ch > 'z') {
                        cout << ans[(i + k - 1) % k] << '\n';
                        f = 1;
                        break;
                    }
                    ans[i] += ch;
                    cnt[ch]--;
                    sm--;
                }
                if (f) break;
                if (ans.back().back() != ans.front().back()) {
                    cout << ans.back() << '\n';
                    break;
                } else {
                    if (cnt[ch] == sm) continue;
                    if (!cnt[ch]) {
                        while (!cnt[ch] && ch <= 'z') ch++;
                        if (cnt[ch] == sm) continue;
                    }
                    {
                        cout << ans.back();
                        while (1) {
                            while (!cnt[ch] && ch <= 'z') ch++;
                            if (ch > 'z') break;
                            cout << ch;
                            cnt[ch]--;
                            sm--;
                        }
                        cout << '\n';
                        break;
                    }
                }
            }
        }
    }
}

signed main() {
#ifdef LOCAL
    std::freopen("input.txt", "r", stdin);
#else
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
#endif
    int t = 1;
    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}