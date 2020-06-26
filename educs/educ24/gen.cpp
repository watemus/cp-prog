//
// Created by watemus on 22.06.2020.
//
//
// Created by watemus on 24.03.2020.
//

#include <bits/stdc++.h>

using namespace std;

signed main(int argc, char **argv) {
    mt19937 rnd(atoi(argv[1]));
    cout << "3000\n";
    for (int i = 0; i < 3000; i++) {
        cout << rnd() % 5 + 1 << ' ';
    }
    return 0;
}
