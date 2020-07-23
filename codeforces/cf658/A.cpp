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
    string a, b;
    cin >> a >> b;
    vec<int> ans;
    int lb, rb;
    lb = 0;
    rb = n - 1;
    bool bord = false;
    for (int i = n - 1; i >= 0; i--) {
        int cr;
        if (!bord) {
            cr = a[lb] - '0';
            lb++;
        } else {
            cr = 1 - (a[rb] - '0');
            rb--;
        }
        bord = !bord;
        if (cr + '0' == b[i]) {
            ans.push_back(1);
        }
        ans.push_back(i + 1);
    }
    cout << ans.size() << '\n';
    for (auto id : ans) {
        cout << id << ' ';
    }
    cout << '\n';
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


