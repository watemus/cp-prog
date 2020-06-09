//
// Created by watemus on 12.05.2020.
//

//
// Created by watemus on 24.03.2020.
//

#include <bits/stdc++.h>

using namespace std;

signed main(int argc, char **argv) {
    mt19937 rnd(atoi(argv[1]));
    cout << 1 << endl;
    int n = 20, k = 1;
    cout << n << ' ' << k << endl;
    for (int i = 0; i < n; i++) {
        cout << rnd() % (k * 2) + 1 << ' ';
    }
    return 0;
}