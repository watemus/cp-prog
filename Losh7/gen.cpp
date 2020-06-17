//
// Created by watemus on 15.06.2020.
//

//
// Created by watemus on 24.03.2020.
//

#include <bits/stdc++.h>

using namespace std;

signed main(int argc, char **argv) {
    mt19937 rnd(atoi(argv[1]));
    int n = 5; int m = 5;
    cout << n << ' ' << m << endl;
    for (int i = 0; i < n; i++) {
        cout << rnd() % 10  + 1 << ' ';
    }
    cout << endl;
    for (int i = 0; i < m; i++) {
        cout << rnd() % n << endl;
    }
    return 0;
}