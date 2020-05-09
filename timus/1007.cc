//
// Created by watemus on 16.04.2020.
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
    int n;
    cin >> n;
    string s;
    while (cin >> s) {
        int sm = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '1') sm += i + 1;
        }
        if (s.size() == n) {
            if (sm % (n + 1) == 0) {
                cout << s << '\n';
                continue;
            }
            for (int i = 0; i < n; i++) {
                if (s[i] == '1' && (sm - i - 1) % (n + 1) == 0) {
                    s[i] = '0';
                    cout << s << '\n';
                    break;
                }
            }
        } else if (s.size() == n - 1) {
            vector<int> scnt(n);
            scnt[s.size() - 1] = s.back() == '1';
            for (int i = s.size() - 2; i >= 0; i--) {
                scnt[i] = scnt[i + 1] + (s[i] == '1');
            }
            for (int ins = 0; ins < n; ins++) {
                if ((sm + scnt[ins] + ins + 1) % (n + 1) == 0) {
                    for (int i = 0; i < ins; i++) cout << s[i];
                    cout << 1;
                    for (int i = ins; i < s.size(); i++) cout << s[i];
                    cout << '\n';
                    break;
                }
                if ((sm + scnt[ins]) % (n + 1) == 0) {
                    for (int i = 0; i < ins; i++) cout << s[i];
                    cout << 0;
                    for (int i = ins; i < s.size(); i++) cout << s[i];
                    cout << '\n';
                    break;
                }
            }
        } else {
            vector<int> scnt(n + 2);
            scnt[s.size() - 1] = s.back() == '1';
            for (int i = s.size() - 2; i >= 0; i--) {
                scnt[i] = scnt[i + 1] + (s[i] == '1');
            }
            for (int rem = 0; rem < s.size(); rem++) {
                int cr = sm - scnt[rem + 1];
                if (s[rem] == '1') cr -= rem + 1;
                if (cr % (n + 1) == 0) {
                    for (int i = 0; i < rem; i++)
                        cout << s[i];
                    for (int i = rem + 1; i < s.size(); i++)
                        cout << s[i];
                    cout << '\n';
                    break;
                }
            }
        }
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