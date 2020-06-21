    //
    // Created by watemus on 17.06.2020.
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
        int a, b, c, n;
        cin >> a >> b >> c >> n;
        vec<int> v1, v2, v3;
        vec<int> coords;
        for (int i = 0; i < n; i++) {
            int y, s;
            cin >> y >> s;
            if (y == 1994) v3.push_back(s);
            if (y == 1995) v2.push_back(s);
            if (y == 1996) v1.push_back(s);
            coords.push_back(s);
        }
        sort(all(coords));
        coords.resize(unique(all(coords)) - coords.begin());
        map<int, int> to;
        for (int i = 0; i < coords.size(); i++) {
            to[coords[i]] = i;
        }
        vec<int> t1(coords.size() + 10), t2(coords.size() + 10), t3(coords.size() + 10);
        for (auto el : v1) t1[to[el]]++;
        for (auto el : v2) t2[to[el]]++;
        for (auto el : v3) t3[to[el]]++;
        for (int i = t1.size() - 2; i >= 0; i--) {
            t1[i] += t1[i + 1];
            t2[i] += t2[i + 1];
            t3[i] += t3[i + 1];
        }
        vec<int> ans(3, -1);
        int ansf = INFL;
        for (int i = 0; i < t1.size(); i++) {
            for (int j = i + 1; j < t1.size(); j++) {
                for (int k = j + 1; k < t1.size(); k++) {
                    if (t1[i] + t2[j] + t3[k] == a + b + c && t1[i] && t2[j] && t3[k]) {
                        int cansf = abs(c - t1[i]) + abs(b - t2[i]) + abs(a - t3[i]);
                        if (cansf < ansf) {
                            ansf = cansf;
                            ans = {t3[k], t2[j], t1[i]};
                        }
                    }
                }
            }
        }
        if (ansf == INFL) {
            cout << "-1\n";
        } else {
            cout << ansf << ' ';
            for (int i : ans) {
                cout << i << " ";
            }
            cout << '\n';
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
        cin >> t;
        while (t--) {
            run();
        }
        return 0;
    }

