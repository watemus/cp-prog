//
// Created by watemus on 03.05.2020.
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
#define int ll

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;

#ifdef LOCAL
#else
#endif

struct Stack {
    Stack *prev = NULL;
    char val;
};

struct TTriplet {
    int a, b, c;
    Stack *st;
};

void run() {
    vector<TTriplet> v;
    int sa, sb, sc;
    int n;
    cin >> n;
    cin >> sa >> sb >> sc;
    v.push_back({sa, sb, sc, nullptr});
    while (n--) {
        string s;
        cin >> s;
        vector<TTriplet> nw;
        if (s == "AB") {
            for (auto el : v) {
                auto t1 = el;
                auto t2 = el;
                t1.a--;
                t1.b++;
                t1.st = new Stack;
                t1.st->val = 'B';
                t1.st->prev = el.st;
                if (t1.a > 0) nw.push_back(t1);
                t2.a++;
                t2.b--;
                t2.st = new Stack;
                t2.st->val = 'A';
                t2.st->prev = el.st;
                if (t2.b > 0) nw.push_back(t2);
            }
        } else if (s == "AC") {
            for (auto el : v) {
                auto t1 = el;
                auto t2 = el;
                t1.a--;
                t1.c++;
                t1.st = new Stack;
                t1.st->val = 'C';
                t1.st->prev = el.st;
                if (t1.a > 0) nw.push_back(t1);
                t2.a++;
                t2.c--;
                t2.st = new Stack;
                t2.st->val = 'A';
                t2.st->prev = el.st;
                if (t2.c > 0) nw.push_back(t2);
            }
        } else if (s == "BC") {
            for (auto el : v) {
                auto t1 = el;
                auto t2 = el;
                t1.b--;
                t1.c++;
                t1.st = new Stack;
                t1.st->val = 'C';
                t1.st->prev = el.st;
                if (t1.b > 0) nw.push_back(t1);
                t2.b++;
                t2.c--;
                t2.st = new Stack;
                t2.st->val = 'B';
                t2.st->prev = el.st;
                if (t2.c > 0) nw.push_back(t2);
            }
        }
        sort(all(nw), [](TTriplet a, TTriplet b){
           return min({a.a, a.b, a.c}) > min({b.a, b.b, b.c});
        });
        while (nw.size() > 50) {
            nw.pop_back();
        }
        v= nw;
    }
    if (v.size()) {
        vector<char> ans;
        Stack *st = v[0].st;
        while (st) {
            ans.push_back(st->val);
            st = st->prev;
        }
        reverse(all(ans));
        cout << "Yes\n";
        for (auto el : ans) {
            cout << el << '\n';
        }
        return;
    }
    cout << "No\n";
}

signed main() {
#ifdef LOCAL
    std::freopen("input.txt", "r", stdin);
#else
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
#endif
    int t = 1;
//    cin >> t;
    while (t--) {
        run();
    }
    return 0;
}