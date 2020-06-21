//
// Created by watemus on 26.04.2020.
//

//
// Created by watemus on 24.03.2020.
//

#include <bits/stdc++.h>

using namespace std;

signed main(int argc, char **argv) {
    mt19937 rnd(atoi(argv[1]));
    int n = 1000;
    int t = 500;
    cout << n << ' ' << t << endl;
    for (int i = 0; i < n; i++) {
        cout << rnd() % 5 + 1 <<  ' ';
    }
    cout << endl;
    for (int i = 0; i < t; i++) {
        int l = rnd() % n + 1;
        int r = rnd() % n + 1;
        cout << "+?"[rnd() % 2] << ' ' << min(l, r) << ' ' << max(l, r) << ' ' << rnd() % 10 << endl;
    }
    return 0;
}