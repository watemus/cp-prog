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

const int MAXN = 3e5;


void run() {
   int n;
   cin >> n;
   vector<vector<int>> d(n, vector<int>(n, INFI));
   for (int i = 0; i < n; i++) d[i][i] = 0;
   for (int i = 0; i < n - 1; i++) {
       int m;
       cin >> m;
       vector<int> a(m);
       for (int j = 0; j < m; j++) cin >> a[j];
       for (int j = 0; j < m; j++) {6
           for (int k = j + 1; k < m; k++) {
               d[a[i]][a[k]] = min(d[a[i]][a[k]], m - 1);
           }
       }
   }
   for (int k = 0; k < n; k++) {
       for (int i = 0; i < n; i++) {
           for (int j = 0; j < n; j++) {
               d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
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
    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}