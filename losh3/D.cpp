//
// Created by watemus on 09.06.2020.
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

//#define int ll

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;
constexpr ld PI = acos(-1);

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

const char TT = '{';

struct Trie {
    Trie *to[27];
    int id;
    Trie() {
        memset(to, 0, sizeof to);
    }
};

void add_string(Trie *root, string &s, int id) {
    root->id = id;
    for (auto ch : s) {
        if (!root->to[ch - 'a']) {
            root->to[ch - 'a'] = new Trie;
        }
        root = root->to[ch - 'a'];
        root->id = id;
    }
}

int check(Trie *root, string &s) {
    for (auto ch : s) {
        if (!root->to[ch - 'a']) {
            return false;
        }
        root = root->to[ch - 'a'];
    }
    return root->id;
}

void run() {
    int n, len;
    cin >> n >> len;
    vec<string> ads(n);
    for (int i = 0; i < n; i++) {
        cin >> ads[i];
    }
    string target;
    cin >> target;
    Trie *root = new Trie;
    int id = 1;
    for (auto &ad : ads) {
        string c_ad = ad;
        for (int pref = 0; pref  < c_ad.size(); pref++) {
            add_string(root, c_ad, id);
            c_ad[pref] = TT;
        }
        id++;
    }
    for (int num_rows = 1; num_rows <= target.size(); num_rows++) {
        for (int offset = 0; offset + target.size() <= num_rows * len; offset++) {
            string cur(offset, TT);
            cur += target;
            vec<string> block(num_rows);
            for (int i = 0; i < cur.size(); i++) {
                block[i % num_rows].push_back(cur[i]);
            }
            vec<int> ans;
            bool bad = false;
            for (auto &row : block) {
                ans.push_back(check(root, row));
                if (ans.back() == 0) {
                    bad = true;
                    break;
                }
            }
            if (!bad) {
                cout << ans.size() << "\n";
                for (auto el : ans) {
                    cout << el << " ";
                }
                cout << '\n';
                return;
            }
        }
    }
    cout << "-1\n";
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

