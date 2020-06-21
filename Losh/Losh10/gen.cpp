//
// Created by watemus on 18.06.2020.
//

//
// Created by watemus on 24.03.2020.
//

#include <bits/stdc++.h>

using namespace std;

signed main(int argc, char **argv) {
    mt19937 rnd(atoi(argv[1]));
    int n = 5, m = 1;
    cout << n << ' ' << m << endl;
    int mp = 1;
    for (int i = 0; i < n; i++) {
        int t = rnd() % 5 + 1;
        mp *= t;
        cout << t << ' ';
    }
    cout << rnd() % mp + 1 << '\n';
    return 0;
}