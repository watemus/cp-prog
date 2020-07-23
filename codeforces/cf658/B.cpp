//
// Created by watemus on 21.07.2020.
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

#define int ll

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
    vec<int> p(n * 2), rp(n * 2);
    for (int i = 0; i < n * 2; i++) {
        cin >> p[i];
        rp[p[i] - 1] = i;
    }
    vec<int> items, used(n * 2);
    for (int i = 2 * n; i >= 1; i--) {
        int at = rp[i - 1];
        int have = 0;
        while (at < 2 * n && !used[at]) {
            have++;
            used[at] = 1;
            at++;
        }
        if (have != 0)
            items.push_back(have);
    }
    vec<int> bp(n + 10);
    bp[0] = 1;
    for (auto item : items) {
        for (int i = bp.size() - 1; i >= 0; i--) {
            if (i + item < bp.size() && bp[i]) {
                bp[i + item] = 1;
            }
        }
    }
    if (bp[n]) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
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


