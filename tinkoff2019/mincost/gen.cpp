//
// Created by watemus on 21.06.2020.
//

#include <bits/stdc++.h>

using namespace std;

signed main(int argc, char **argv) {
    mt19937 rnd(atoi(argv[1]));
    int n = 4;
    int lim = 10;
    cout << n << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << rnd() % lim << ' ';
        }
        cout << '\n';
    }
    return 0;
}