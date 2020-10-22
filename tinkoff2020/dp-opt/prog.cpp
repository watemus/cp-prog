//
// Created by watemus on 22.10.2020.
//

#include <bits/stdc++.h>

using namespace std;

int main() {
  vector<string> names = {"Anton", "Boris", "Victor"};
  vector<int> ages(3);
  for (int i = 0; i < 3; i++) {
    cout << names[i] << ": ";
    cin >> ages[i];
  }
  set<string> ans;
  int mx = -1;
  for (int i = 0; i < 3; i++) {
    if (ages[i] > mx) {
      ans.clear();
      mx = ages[i];
      ans.insert(names[i]);
    } else if (ages[i] == mx) {
      ans.insert(names[i]);
    }
  }
  for (const auto &name : ans) {
    cout << name << " ";
  }
  if (ans.size() == 3) {
    cout << "are peers.\n";
  } else if (ans.size() == 2) {
    cout << "are older than ";
    for (int i = 0; i < 3; i++) {
      if (!ans.count(names[i])) {
        cout << names[i] << '\n';
      }
    }
  } else {
    cout << "is older than ";
    for (int i = 0; i < 3; i++) {
      if (!ans.count(names[i])) {
        cout << names[i] << ' ';
      }
    }
    cout << '\n';
  }
  return 0;
}