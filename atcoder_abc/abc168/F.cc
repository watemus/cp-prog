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

struct Segment {
    int x1, x2, y;
};

void run() {
    int n, m;
    cin >> n >> m;
    vec<Segment> hor_segments(n), ver_segments(m);
    vec<int> xs, ys;
    for (auto &[x1, x2, y] : hor_segments) {
        cin >> x1 >> x2 >> y;
        xs.push_back(x1);
        xs.push_back(x2);
        ys.push_back(y);
    }
    for (auto &[y1, y2, x] : ver_segments) {
        cin >> x >> y1 >> y2;
        ys.push_back(y1);
        ys.push_back(y2);
        xs.push_back(x);
    }
    xs.push_back(INFI);
    xs.push_back(-INFI);
    ys.push_back(INFI);
    ys.push_back(-INFI);
    sort(all(xs));
    sort(all(ys));
    xs.resize(unique(all(xs)) - xs.begin());
    ys.resize(unique(all(ys)) - ys.begin());
    vec<int> fx, fy;
    for (auto x : xs) {
        fx.push_back(x);
        fx.push_back(x);
    }
    for (auto y : ys) {
        fy.push_back(y);
        fy.push_back(y);
    }
    int height = fx.size();
    int width = fy.size();
    vec<vec<int>> color(height, vec<int>(width));
    for (auto [x1, x2, y] : hor_segments) {
        int target_j = 0;
        for (int i = 0; i < fy.size(); i++) {
            if (fy[i] == y) {
                target_j = i;
                break;
            }
        }
        for (int i = 0; i < height - 1; i++) {
            if (fx[i] >= x1 && fx[i + 1] <= x2) {
                color[i][target_j] = 1;
            }
        }
    }
    for (auto [y1, y2, x] : ver_segments) {
        int target_i = 0;
        for (int i = 0; i < fx.size(); i++) {
            if (fx[i] == x) {
                target_i = i;
                break;
            }
        }
        for (int i = 0; i < width - 1; i++) {
            if (fy[i] >= y1 && y2 >= fy[i + 1]) {
                color[target_i][i] = 1;
            }
        }
    }
    int start_i, start_j;
    bool found = false;
    for (int i = 0; i < height - 1; i++) {
        for (int j = 0; j < width - 1; j++) {
            if (fx[i] <= 0 && fx[i + 1] >= 0 && fy[j] <= 0 && fy[j + 1] >= 0 && color[i][j] != 1) {
                start_i = i;
                start_j = j;
                found = true;
            }
        }
    }
    if (!found) exit(0);
    int ans = 0;
    vec<vec<int>> usd(height, vec<int>(width));
    function<void(int, int)> bfs = [&](int i, int j) {
        queue<pair<int, int>> q;
        q.push({i, j});
        usd[i][j] = 1;
        while (q.size()) {
            i = q.front().first;
            j = q.front().second;
            q.pop();
            usd[i][j] = 1;
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                cout << "INF\n";
                exit(0);
            }
            ans += (fy[j + 1] - fy[j]) * (fx[i + 1] - fx[i]);
            for (auto[di, dj] : DD) {
                if (!usd[i + di][j + dj] && !color[i + di][j + dj]) {
                    q.push({i + di, j + dj});
                    usd[i + di][j + dj] = 1;
                }
            }
        }
    };
    bfs(start_i, start_j);
    cout << ans << '\n';
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

