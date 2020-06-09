//
// Created by watemus on 18.05.2020.
//
//
// Created by watemus on 24.03.2020.
//

#include <bits/stdc++.h>

using namespace std;

signed main(int argc, char **argv) {
    mt19937 rnd(atoi(argv[1]));
    int n = 400;
    cout << n << endl;
    for (int i = 0; i < n; i++) {
        cout << rnd() % n + 1 << ' ';
    }
    cout << endl;
    return 0;
}
