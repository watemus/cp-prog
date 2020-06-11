//
// Created by watemus on 10.06.2020.
//

#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif
#include <bits/stdc++.h>


#ifndef LOCAL
#pragma GCC optimize("Ofast")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("vpt")
#endif

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

//#define int ll

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;
constexpr ld PI = acos(-1);

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
const int BLOCK = 500;
#else
const int BLOCK = 500;
#endif

const int MAXN = 1e5 + 1000;

int used[MAXN];
int used_block[BLOCK];
int ans_block[BLOCK][BLOCK];
int pos_ans_block[BLOCK][BLOCK];

void run() {
    int n, k;
    cin >> n >> k;
    if (k >= 100) {
        vec<deque<int>> a((n + k - 1) / k);
        for (int i = 0; i < n; i++) {
            int el;
            cin >> el;
            a[i / k].push_back(el);
        }
        while (a.size()) {
            int at = 0;
            for (int i = 0; i < a.size(); i++) {
                if (a[i].front() > a[at].front()) {
                    at = i;
                }
            }
            cout << a[at].front() << '\n';
            a[at].pop_front();
            for (int i = at; i < a.size() - 1; i++) {
                a[i].push_back(a[i + 1].front());
                a[i + 1].pop_front();
            }
            if (a.back().empty()) a.pop_back();
        }
    } else {
        memset(used, 0, sizeof used);
        memset(used_block, 0, sizeof used_block);
        for (int i = 0; i < BLOCK; i++) {
            memset(ans_block[i], -1, sizeof ans_block[i]);
            memset(pos_ans_block[i], -1, sizeof pos_ans_block[i]);
        }
        vec<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            if (a[i] > ans_block[i / BLOCK][i % k]) {
                ans_block[i / BLOCK][i % k] = a[i];
                pos_ans_block[i / BLOCK][i % k] = i;
            }
        }
        for (int iter = 0; iter < n; iter++) {
            int removed = 0;
            int cnt_blocks = (n + BLOCK - 1) / BLOCK;
            int ans = -1;
            int pos_ans = -1;
            for (int i = 0; i < cnt_blocks; i++) {
                if (ans_block[i][removed % k] > ans) {
                    ans = ans_block[i][removed % k];
                    pos_ans = pos_ans_block[i][removed % k];
                }
                removed += used_block[i];
            }
            cout << ans << '\n';
            used[pos_ans] = 1;
            a[pos_ans] = -1;
            memset(ans_block[pos_ans / BLOCK], -1, sizeof ans_block[pos_ans / BLOCK]);
            memset(pos_ans_block[pos_ans / BLOCK], 0, sizeof pos_ans_block[pos_ans / BLOCK]);

            used_block[pos_ans / BLOCK]++;
            int start_block = pos_ans / BLOCK * BLOCK;
            int block_removed = 0;
            for (int i = start_block; i < min(n, start_block + BLOCK); i++) {
                if (used[i]) {
                    block_removed++;
                }
                if (a[i] > ans_block[i / BLOCK][((i - block_removed) % k + k) % k]) {
                    ans_block[i / BLOCK][((i - block_removed) % k + k) % k] = a[i];
                    pos_ans_block[i / BLOCK][((i - block_removed) % k + k) % k] = i;
                }
            }

        }
    }

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

