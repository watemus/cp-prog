//
// Created by watemus on 18.06.2020.
//

//
// Created by watemus on 24.03.2020.
//

#include <bits/stdc++.h>

using namespace std;

signed main(int argc, char **argv) {
    mt19937 rnd;
    int n = 200;
    cout << n << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 10; j++) {
            cout << char(rnd() % 26 + 'a');
        }
        cout << '\n';
    }
    return 0;
}