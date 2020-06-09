//
// Created by watemus on 16.05.2020.
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

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

const int MAXN =  55;

void run() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        reverse(all(s));
        int nm = 0;
        for (int j = 0; j < m; j++) {
            if (s[j] == '1') nm += (1ULL << j);
        }
        a[i] = nm;
    }
    sort(all(a));
    int fnd = ((1 << m) - n - 1) / 2;
    int lb = -1;
    int rb = (1 << m) + 1;
    while (lb + 1  < rb) {
        int mid = (lb + rb) / 2;
        int cnt = mid;
        for (auto el : a) {
            if (el <= mid) cnt--;
        }
        if (cnt >= fnd) {
            rb = mid;
        } else {
            lb = mid + 1;
        }
    }
    string ans;
    while (lb > 0) {
        ans.push_back('0' + lb % 2);
        lb /= 2;
    }
    while (ans.size() < m) ans.push_back('0');
    reverse(all(ans));
    cout << ans << '\n';
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