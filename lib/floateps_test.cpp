//
// Created by watemus on 26.06.2020.
//

#include <bits/stdc++.h>
#include "../lib/floateps.cpp"

int main() {
    ldp a = 4;
    std::cout << a << std::endl;
    a -= 1;
    a += 0.9;
    a += 0.1;
    std::cout << a << std::endl;
    std::cout << (a == ldp(4.0001)) << std::endl;
}