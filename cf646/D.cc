//
// Created by watemus on 31.05.2020.
//

#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif
#include <bits/stdc++.h>

using namespace std;

int ask(vector<int> &t) {

    cout << "? " << t.size();
    for (auto el : t) {
        cout << ' ' << el;
    }
    cout << endl;
    int ans;
    cin >> ans;
    if (ans == -1) exit(0);
    return ans;
}

void run() {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> c(k);
    vector<int> all(n);
    for (int i = 0; i < k; i++) {
        int m;
        cin >> m;
        c[i].resize(m);
        for (auto &el : c[i]) {
            cin >> el;
        }
    }
    for (int i = 0; i < n; i++) {
        all[i] = i + 1;
    }
    int mx = ask(all);
    int lb = 0;
    int rb = n;
    while (lb + 1 < rb) {
        int mid = (lb + rb) / 2;
        vector<int> cur;
        for (int i = lb; i < mid; i++) {
            cur.push_back(all[i]);
        }
        int val = ask(cur);
        if (val == mx) {
            rb = mid;
        } else {
            lb = mid;
        }
    }
    int needle = all[lb];
    int id = -1;
    for (int i = 0; i < k; i++) {
        for (auto el : c[i]) {
            if (el == needle) {
                id = i;
                break;
            }
        }
        if (id != -1)
            break;
    }
    set<int> with;
    vector<int> without;
    if (id != -1) {
        for (auto el : c[id]) with.insert(el);
    }
    for (int i = 0; i < n; i++) {
        if (!with.count(i + 1)) without.push_back(i + 1);
    }
    int val = ask(without);
    cout << "! ";
    for (int i = 0; i < k; i++) {
        if (i == id) {
            cout << val << ' ';
        } else {
            cout << mx << ' ';
        }
    }
    string s;
    cin >> s;
    if (s != "Correct") exit(0);
}

signed main() {
#ifdef LOCAL
    //std::freopen("input.txt", "r", stdin);
#else

#endif
    int t = 1;
    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}