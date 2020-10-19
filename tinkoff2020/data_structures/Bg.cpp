//Anton Gorokhov, [11.10.20 10:00]
#ifdef lolipop
#define _GLIBCXX_DEBUG
#endif

/*
    This ain't a milly rock
    This a money dance
    And my D' ain't hard
    That's a .30 in my pants
*/

#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>
#include <set>
#include <map>
#include <ctime>
#include <unordered_map>
#include <random>
#include <iomanip>
#include <cmath>
#include <queue>
#include <unordered_set>
#include <cassert>
#include <bitset>
#include <deque>
#include <utility>

#define int long long
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define ld long double

using namespace std;

mt19937 rnd(229);

inline void fastio() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
}

struct node {
  node *l = nullptr, *r = nullptr;
  int x, y;
  // x - key, y - random stuff
  int sum = 0;
  int size = 0;
  // sum - sum of the keys in the subtree
  node() {}
  node(int _x) : x(_x), y(rnd() % 1000000), sum(_x), size(1LL) {}
};

int size(node *root) {
  if (!root) return 0LL;
  return root->size;
}

int sum(node *root) {
  if (!root) return 0LL;
  return root->sum;
}

void update(node *root) {
  if (!root) return;
  root->sum = sum(root->l) + root->x + sum(root->r);
  root->size = size(root->l) + 1 + size(root->r);
}

node *merge(node *L, node *R) {
  if (!L) return R;
  if (!R) return L;
  update(L);
  update(R);
  if (L->y < R->y) {
    node *T = merge(L->r, R);
    L->r = T;
    update(L);
    return L;
  } else {
    node *T = merge(L, R->l);
    R->l = T;
    update(R);
    return R;
  }
}

pair<node*, node*> split(node *root, int k) {
  if (!root) {
    return make_pair(nullptr, nullptr);
  }
  update(root);
  // in L there will be keys <= k
  if (root->x <= k) {
    pair<node*, node*> T = split(root->r, k);
    root->r = T.first;
    update(root);
    return make_pair(root, T.second);
  } else {
    pair<node*, node*> T = split(root->l, k);
    root->l = T.second;
    update(root);
    return make_pair(T.first, root);
  }
}

node *insert(node *root, int x) {
  pair<node*, node*> T = split(root, x);
  return merge(T.first, merge(new node(x), T.second));
}

node *erase(node *root, int x) {
  if (!root) return nullptr;
  if (root->x == x) {
    return merge(root->l, root->r);
  }
  if (root->x > x) {
    root->l = erase(root->l, x);
    update(root);
    return root;
  } else {
    root->r = erase(root->r, x);
    update(root);
    return root;
  }
}

pair<node*, int> getans(node *root, int y1, int y2) {
  pair<node*, node*> LR = split(root, y2);
  pair<node*, node*> LL = split(LR.first, y1 - 1);
  int localans = size(LR.second) * (y2 - y1) + sum(LL.second) - y1 * size(LL.second);
  return make_pair(merge(merge(LL.first, LL.second), LR.second), localans);
}

struct mst {
  mst *l = nullptr, *r = nullptr;
  int lb, rb;
  node *val = nullptr;
  mst() {}
  mst(int L, int R, const vector<int> &vec) {
    lb = L, rb = R;
    if (lb + 1 == rb) {
      val = new node(vec[lb]);
    } else {
      for (int i = L; i < R; ++i) {
        val = insert(val, vec[i]);
      }
      int m = (lb + rb) / 2;
      l = new mst(lb, m, vec);
      r = new mst(m, rb, vec);
    }
  }
  void update(int pos, int oldval, int nval) {
    if (lb + 1 == rb) {
      val = new node(nval);
    } else {
      val = erase(val, oldval);
      val = insert(val, nval);
      int m = (lb + rb) / 2;
      if (pos < m) {
        l->update(pos, oldval, nval);
      } else {
        r->update(pos, oldval, nval);
      }
    }
  }
  int get(int L, int R, int y1, int y2) {
    if (L >= rb || lb >= R) {
      return 0;
    }
    if (L <= lb && R >= rb)  {
      pair<node*, int> got = getans(val, y1, y2);
      val = got.first;

//      Anton Gorokhov, [11.10.20 10:00]
      return got.second;
    }
    return l->get(L, R, y1, y2) + r->get(L, R, y1, y2);
  }
};

void query(mst *root) {
  int x1, x2, y1, y2;
  cin >> x1 >> y1 >> x2 >> y2;
  int S = root->get(x1 - 1, x2, y1, y2);
  if (S * 2 == (x2 - x1 + 1) * (y2 - y1)) {
    cout << "0\n";
  } else {
    if (S * 2 > (x2 - x1 + 1) * (y2 - y1)) {
      cout << "2\n";
    } else {
      cout << "1\n";
    }
  }
}

void dfs(mst *root) {
  if (!root) return;
  dfs(root->l);
  if (!(root->l)) {
    cout << sum(root->val) << ' ';
    return;
  }
  dfs(root->r);
}

void print(mst *root) {
  cout << "[ ";
  dfs(root);
  cout << "]";
  cout << '\n';
}

void solve() {
  int n;
  cin >> n;
  vector<int> v(n);
  for (int i = 0; i < n; ++i) {
    cin >> v[i];
  }
  mst *root = new mst(0, n, v);
//    print(root);
  int m;
  cin >> m;
  while (m--) {
    char c;
    cin >> c;
    if (c == 'Q') {
      query(root);
    } else {
      int pos, nval;
      cin >> pos >> nval;
      pos--;
      root->update(pos, v[pos], nval);
      v[pos] = nval;
//            print(root);
    }
  }
}

signed main() {
#ifdef lolipop
  freopen("input.txt", "r", stdin);
#else
  fastio();
#endif

  int T = 1;
//    cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}