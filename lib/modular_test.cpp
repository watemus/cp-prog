//
// Created by watemus on 26.06.2020.
//
#include <bits/stdc++.h>
#include "modular.cpp"

constexpr int MOD1 = 1e9 + 7;
constexpr int MOD2 = 1e9 + 9;
constexpr int MOD3 = 998244353;

signed main() {
    tmll<MOD1, MOD2, MOD3> a(2);
    a += 3;
    a += MOD1;
    std::cout << a.v1.val << " " << a.v2.val << " " << a.v3.val << std::endl;
    a = a - tmll<MOD1, MOD2, MOD3>(MOD1);
    std::cout << a.v1.val << " " << a.v2.val << " " << a.v3.val << std::endl;
}