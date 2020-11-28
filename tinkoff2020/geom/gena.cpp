//
// Created by watemus on 22.11.2020.
//

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char **argv) {
  mt19937 rnd(atoi(argv[1]));
  {
    int x = rnd() % 10;
    int y = rnd() % 10;
    cout << x << ' ' << y << endl;
    int nx = rnd() % 10;
    int ny = rnd() % 10;
    while (x == nx && y == ny) {
      nx = rnd() % 10;
      ny = rnd() % 10;
    }
    cout << nx << ' ' << ny << endl;
  }
  {
    int x = rnd() % 10;
    int y = rnd() % 10;
    cout << x << ' ' << y << endl;
    int nx = rnd() % 10;
    int ny = rnd() % 10;
    while (x == nx && y == ny) {
      nx = rnd() % 10;
      ny = rnd() % 10;
    }
    cout << nx << ' ' << ny << endl;
  }
  return 0;
}