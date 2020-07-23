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

const int MAXN = 1e5 + 10;

class seg_tree {

    int n;

    struct node {
        int val;
        int at;
    };

    vec<node> t;

    inline void _upd(int v) {
        if (t[v * 2 + 1].val > t[v * 2 + 2].val) {
            t[v] = t[v * 2 + 1];
        } else {
            t[v] = t[v * 2 + 2];
        }
    }

    void _build(int v, int lb, int rb, vec<int> &arr) {
        if (rb - lb == 1) {
            t[v].val = arr[lb];
            t[v].at = lb;
        } else {
            int mid = (lb + rb) / 2;
            _build(v * 2 + 1, lb, mid, arr);
            _build(v * 2 + 2, mid, rb, arr);
            _upd(v);
        }
    }

    void _modify(int v, int lb, int rb, int at, int dt) {
        if (rb - lb == 1) {
            t[v].val += dt;
        } else {
            int mid = (lb + rb) / 2;
            if (at < mid) {
                _modify(v * 2 + 1, lb, mid, at, dt);
            } else {
                _modify(v * 2 + 2, mid, rb, at, dt);
            }
            _upd(v);
        }
    }
public:
    seg_tree(int n, vec<int> &arr)
        : n(n), t(n * 4)
    {
        _build(0, 0, n, arr);
    }

    inline pair<int, int> get() {
        return {t[0].val, t[0].at};
    }

    inline void modify(int at, int dt) {
        _modify(0, 0, n, at, dt);
    }
};

void run() {
    int n, x, y;
    cin >> n >> x >> y;
    vec<int> a(n), cnt(n + 1);
    vec<vec<int>> pos(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        cnt[a[i] - 1]++;
        pos[a[i] - 1].push_back(i);
    }
    int rem = -1;
    for (int i = 0; i <= n; i++) {
        if (cnt[i] == 0) {
            rem = i;
            break;
        }
    }
    seg_tree st(n + 1, cnt);
    vec<int> ans(n, -1);
    for (int i = 0; i < x; i++) {
        auto [cur_cnt, clr] = st.get();
        cnt[clr]--;
        st.modify(clr, -1);
        int at = pos[clr].back();
        pos[clr].pop_back();
        ans[at] = clr + 1;
    }
    y -= x;
    vec<pair<int, int>> to_change;
    int have = n - x;
    while (have > 0) {
        auto [cur_cnt, clr] = st.get();
        if (cur_cnt <= have / 2) {
            break;
        }
        cnt[clr]--;
        have--;
        st.modify(clr, -1);
        int at = pos[clr].back();
        pos[clr].pop_back();
        ans[at] = rem + 1;
    }
    for (int i = 0; i < n; i++) {
        if (ans[i] == -1) {
            to_change.emplace_back(a[i] - 1, i);
        }
    }
    if (to_change.size() < y || to_change.size() == 1) {
        cout << "NO\n";
        return;
    }
    sort(ALL(to_change));
    auto changed = to_change;
    rotate(changed.begin(), changed.begin() + changed.size() / 2, changed.end());
    for (int i = 0; i < y; i++) {
        ans[changed[i].second] = to_change[i].first + 1;
    }
    for (int i = 0; i < n; i++) {
        if (ans[i] == -1) ans[i] = rem + 1;
    }
    cout << "YES\n";
    for (auto el : ans) {
        cout << el << ' ';
    }
    cout << "\n";
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


