//
// Created by watemus on 18.06.2020.
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

tuple<vec<int>, vec<int>, vec<int>> get_frac(int a, int k) {
    int integer = a / k;
    int md = a % k;
    vec<int> vint;
    while (integer > 0) {
        vint.push_back(integer % 10);
        integer /= 10;
    }
    if (vint.size() == 0) vint.push_back(0);
    reverse(all(vint));
    vec<pair<int, int>> frac;
    set<int> was;
    while (!was.count(md) && md != 0) {
        was.insert(md);
        frac.emplace_back(md, (md * 10) / k);
        md = (md * 10) % k;
    }
    vec<int> vfrac, vper;
    bool per = false;
    for (auto mdd : frac) {
        if (mdd.first == md) {
            per = true;
        }
        if (per) vper.push_back(mdd.second);
        else vfrac.push_back(mdd.second);
    }
    return {vint, vfrac, vper};
}

void run() {
    int n, k;
    cin >> n >> k;
    vec<int> vint, vfrac, vper;
    tie(vint, vfrac, vper) = get_frac(n, k);
#ifdef LOCAL
    for (auto el : vint) {
        cout << el;
    }
    cout << ",";
    for (auto el : vfrac) {
        cout << el;
    }
    cout << "(";
    for (auto el : vper) {
        cout << el;
    }
    cout << ")";
    cout << endl;
#endif
    vec<string> ans;
    int smi = 0, smf = 0, smp = 0;
    for (auto el : vint) smi += el;
    for (auto el : vfrac) smf += el;
    for (auto el : vper) smp += el;
    while (smi + smf + smp > 0) {
        ans.push_back("");
        bool was = false;
        if (smi == 0) {
            ans.back().push_back('0');
            was = true;
        } else {
            for (auto &el : vint) {
                if (el > 0) {
                    ans.back().push_back('0' + k);
                    el--;
                    smi--;
                    was = true;
                } else if (was) {
                    ans.back().push_back('0');
                }
            }
        }
        if (smf + smp) {
            string frac;
            for (auto &el : vfrac) {
                if (smf > 0 || smp) {
                    if (el != 0) {
                        frac.push_back('0' + k);
                        el--;
                        smf--;
                    } else {
                        frac.push_back('0');
                    }
                }
            }
            if (smp) {
                string per;
                for (auto &el : vper) {
                    if (el) {
                        el--;
                        smp--;
                        per.push_back('0' + k);
                    } else {
                        per.push_back('0');
                    }
                }
                for (int d = 1; d < per.size(); d++) {
                    if (per.size() % d) continue;
                    set<string> st;
                    string cr;
                    for (int i = 0; i < per.size(); i++) {
                        cr.push_back(per[i]);
                        if (i % d == d - 1) {
                            st.insert(cr);
                            cr.clear();
                        }
                    }
                    if (st.size() == 1) {
                        per = *st.begin();
                        break;
                    }
                }
                while (frac.size() >= per.size()) {
                    string cr;
                    for (int i = frac.size() - per.size(); i < frac.size(); i++) {
                        cr.push_back(frac[i]);
                    }
                    if (cr != per) break;
                    else {
                        for (int i = 0; i < per.size(); i++) {
                            frac.pop_back();
                        }
                    }
                }
                ans.back().push_back('.');
                ans.back() += frac;
                ans.back().push_back('(');
                ans.back() += per;
                ans.back().push_back(')');
            } else {
                ans.back().push_back('.');
                ans.back() += frac;
            }
        }
    }
    cout << n << "=";
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << "+\n"[i==ans.size()-1];
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

