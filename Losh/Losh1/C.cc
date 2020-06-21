//
// Created by watemus on 08.06.2020.
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
constexpr ld PI = acos(-1);

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

pair<int, int> rot(pair<int, int> a) {
    return {a.second, -a.first};
}

pair<int, int> rv(pair<int, int> a) {
    return {-a.first, -a.second};
}

const int MAXN = 30;
const int ROTS = 4;
const int MAXK = 6;

int dist[MAXN][MAXN][MAXK][ROTS];
int f[MAXN][MAXN];

void run() {
    int k, n, m;
    cin >> k >> n >> m;
    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < MAXN; j++) {
            for (int h = 0; h < MAXK; h++) {
                memset(dist[i][j][h], -1, sizeof dist[i][j][h]);
            }
        }
    }
    for (int i = 0; i < MAXN; i++) {
        fill(f[i], f[i] + MAXN, 1);
    }
    int sx, sy, fx, fy;
    sx = sy = fx = fy = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> f[i][j];
            if (f[i][j] == 2) {
                sx = i;
                sy = j;
            } else if (f[i][j] == 3) {
                fx = i;
                fy = j;
            }
        }
    }
    queue<tuple<int, int, int, int>> q;
    dist[sx][sy][0][0] = 0;
    dist[sx][sy][0][1] = 0;
    dist[sx][sy][0][2] = 0;
    dist[sx][sy][0][3] = 0;
    q.push({sx, sy, 0, 0});
    q.push({sx, sy, 0, 1});
    q.push({sx, sy, 0, 2});
    q.push({sx, sy, 0, 3});
    while (q.size()) {
        auto [x, y, cnt, prev_rot] = q.front();
        int dst = dist[x][y][cnt][prev_rot];
        q.pop();
        for (int new_rot = 0; new_rot < DD.size(); new_rot++) {
            int dx = DD[new_rot].first;
            int dy = DD[new_rot].second;
            int dcnt = (rot(DD[prev_rot]) == DD[new_rot]);
            if (cnt + dcnt > k) continue;
            if (rv(DD[new_rot]) == DD[prev_rot]) continue;
            if (dist[x+dx][y+dy][cnt+dcnt][new_rot] == -1 && f[x+dx][y+dy] != 1) {
                dist[x+dx][y+dy][cnt+dcnt][new_rot] = dist[x][y][cnt][prev_rot] + 1;
                q.push({x+dx, y+dy, cnt+dcnt, new_rot});
            }
        }
    }
    int ans = INFL;
    for (int cnt = 0; cnt <= k; cnt++) {
        for (int prot = 0; prot < 4; prot++) {
            if (dist[fx][fy][cnt][prot] != -1) {
                ans = min(ans, dist[fx][fy][cnt][prot]);
            }
        }
    }
    cout << (ans == INFL ? -1 : ans) << '\n';
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

