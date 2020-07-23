//
// Created by watemus on 19.07.2020.
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
using vec = std::vector<T>;

template<typename T>
using uset = std::unordered_set<T>;

template<typename T1, typename T2>
using umap = std::unordered_map<T1, T2>;

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;
const ld PI = acos(-1);
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

vec<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

void run() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    string t = "abacaba";
    for (int i = 0; i + t.size() <= s.size(); i++) {
        string st = s;
        bool ok = true;
        for (int j = 0; j < t.size(); j++) {
            if (s[i + j] != t[j] && s[i + j] != '?') {
                ok = false;
                break;
            }
            st[i + j] = t[j];
        }
        if (ok) {
            for (int j = 0; j < i; j++) {
                if (st[j] == '?') st[j] = 'z';
            }
            for (int j = i + t.size(); j < s.size(); j++) {
                if (st[j] == '?') st[j] = 'z';
            }
            for (int j = 0; j + t.size() <= s.size(); j++) {
                if (j == i) continue;
                bool bad = true;
                for (int k = 0; k < t.size(); k++) {
                    if (st[k + j] != t[k]) {
                        bad = false;
                        break;
                    }
                }
                if (bad) {
                    ok = false;
                    break;
                }
            }
        }
        if (ok) {
            cout << "Yes\n";
            cout << st << '\n';
            return;
        }
    }
    cout << "No\n";
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


