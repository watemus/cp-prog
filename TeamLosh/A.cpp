//
// Created by watemus on 19.06.2020.
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
    int n;
    cin >> n;
    vec<string> names(n);
    vec<vec<string>> nums(n);
    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        nums[i].resize(m);
        cin >> names[i];
        for (int j = 0; j < m; j++) {
            int a, b, c;
            char ch;
            cin >> a >> ch >> b >> ch >> c;
            auto sa = to_string(a);
            auto sb = to_string(b);
            auto sc = to_string(c);
            if (sa.size() == 1) sa = string("0") + sa;
            if (sb.size() == 1) sb = string("0") + sb;
            if (sc.size() == 1) sc = string("0") + sc;
            nums[i][j] = sa + sb + sc;
        }
    }
    vec<int> cnt_taxi(n), cnt_pizza(n), cnt_oth(n);
    for (int i = 0; i < n; i++) {
        for (auto num : nums[i]) {
            set<int> digs;
            bool is_piz = true;
            int pr = 10;
            auto snum = num;
            for (char ch : snum) {
                digs.insert(ch);
                if (ch - '0' >= pr) {
                    is_piz = false;
                }
                pr = ch - '0';
            }
            if (digs.size() == 1) cnt_taxi[i]++;
            else if (is_piz) cnt_pizza[i]++;
            else cnt_oth[i]++;
        }
    }
    int mxt = 0, mxp = 0, mxo = 0;
    vec<int> vt, vp, vo;
    for (int i = 0; i < n; i++) {
        if (cnt_taxi[i] > cnt_taxi[mxt]) {
            mxt = i;
            vt.clear();
            vt.push_back(i);
        } else if (cnt_taxi[i] == cnt_taxi[mxt]) {
            vt.push_back(i);
        }
        if (cnt_pizza[i] > cnt_pizza[mxp]) {
            mxp = i;
            vp.clear();
            vp.push_back(i);
        } else if (cnt_pizza[i] == cnt_pizza[mxp]) {
            vp.push_back(i);
        }
        if (cnt_oth[i] > cnt_oth[mxo]) {
            mxo = i;
            vo.clear();
            vo.push_back(i);
        } else if (cnt_oth[i] == cnt_oth[mxo]) {
            vo.push_back(i);
        }
    }
    cout << "If you want to call a taxi, you should call: ";
    int i = 0;
    for (auto el : vt) {
        cout << names[el] << ",."[i==vt.size()-1];
        if (i < vt.size() - 1) cout << " ";
        i++;
    }
    cout << '\n';
    cout << "If you want to order a pizza, you should call: ";
    i=0;
    for (auto el : vp) {
        cout << names[el] << ",."[i==vp.size()-1];
        if (i < vp.size() - 1) cout << " ";
        i++;
    }
    cout << '\n';
    cout << "If you want to go to a cafe with a wonderful girl, you should call: ";
    i=0;
    for (auto el : vo) {
        cout << names[el] << ",."[i==vo.size()-1];
        if (i < vo.size() - 1) cout << " ";
        i++;;
    }
    cout << '\n';
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

