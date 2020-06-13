//
// Created by watemus on 13.06.2020.
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
const ld PI = acos(-1);

vector<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

void run() {
    string s;
    cin >> s;
    vector<int> st;
    queue<int> q;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(') {
            st.push_back(i);
        } else if (s[i] == ')'){
            if (st.size()) {
                st.pop_back();
            } else {
                q.push(i);
            }
        }
    }
    queue<int> qst;
    for (int i = 0; i < st.size(); i++) {
        qst.push(st[i]);
    }
    bool was = false;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] != '?') {
            cout << s[i];
            continue;
        }
        while (q.size() && q.front() < i) {
            q.pop();
        }
        if (q.size()) {
            cout << '(';
            q.pop();
        } else if (qst.size() && qst.front() < i) {
            cout << ')';
            qst.pop();
        } else {
            if (!was) {
                cout << '(';
            } else {
                cout << ')';
            }
            was = !was;
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

