//
// Created by watemus on 03.08.2020.
//

#ifdef LOCAL
#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif

#include <bits/stdc++.h>

using namespace std;

#define ALL(a) a.begin(), a.end()
#define RALL(a) a.rbegin(), a.rend()
#define FF first
#define SS second

using ll = long long;
using ld = long double;

#define int ll

template<typename T>
using vec = std::vector<T>;

template<typename T>
using uset = std::unordered_set<T>;

template<typename T1, typename T2>
using umap = std::unordered_map<T1, T2>;

constexpr ll INFL = 1'000'000'000'000'000'228;
constexpr int INFI = 1'000'000'228;
const ld PI = acos(-1);
std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

vec<pair<int, int>> DD = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

#ifdef LOCAL
#else
#endif

struct SplayTree {
  struct Node {
    int size;
    int value;
    bool reversed;
    Node *left, *right;
    Node *parent;
    Node(int value)
    : size(1), value(value), reversed(false),
    left(nullptr), right(nullptr), parent(nullptr) {}
  };
  static inline int size(Node *node) {
    return (node ? node->size : 0);
  }
  static inline void reverse(Node *node) {
    if (node) {
      node->reversed = !node->reversed;
    }
  }
  static inline void push(Node *node) {
    if (node) {
      node->size = size(node->left) + size(node->right) + 1;
      if (node->reversed) {
        swap(node->left, node->right);
        reverse(node->left);
        reverse(node->right);
      }
    }
  }
  static inline void update_parent(Node *node, Node *parent) {
    if (node) {
      node->parent = parent;
    }
  }
  static inline void rotate_left(Node *node) {
    auto parent = node->parent;
    auto son = node->right;
    if (parent) {
      if (parent->left == node) {
        parent->left = son;
      } else {
        parent->right = son;
      }
    }
    auto son_left = son->left;
    son->left = node;
    node->right = son_left;
    update_parent(node, son);
    update_parent(son, parent);
    update_parent(node->right, node);
  }
  static inline void rotate_right(Node *node) {
    auto parent = node->parent;
    auto son = node->left;
    push(parent);
    push(node);
    push(son);
    if (parent) {
      if (parent->left == node) {
        parent->left = son;
      } else {
        parent->right = son;
      }
    }
    auto son_right = son->right;
    son->right = node;
    node->left = son->right;
    update_parent(node, son);
    update_parent(son, parent);
    update_parent(node->left, node);
  }
  static inline void splay(Node *node) {
    while (node->parent) {
      if (node == node->parent->left) {
        if (node->parent->parent == nullptr) {
          rotate_right(node->parent);
        } else if (node->parent->parent->left == node->parent) {
          rotate_right(node->parent->parent);
          rotate_right(node->parent);
        } else {
          rotate_right(node->parent->parent);
          rotate_left(node->parent);
        }
      } else {
        if (node->parent->parent == nullptr) {
          rotate_left(node->parent);
        } else if (node->parent->parent->right == node->parent) {
          rotate_left(node->parent->parent);
          rotate_left(node->parent);
        } else {
          rotate_left(node->parent->parent);
          rotate_right(node->parent);
        }
      }
    }
  }
};

void run() {

}

signed main() {
#ifdef LOCAL
  std::freopen("input.txt", "r", stdin);
#else
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
#endif
  int t = 1;
  //cin >> t;
  while (t--) {
    run();
  }
  return 0;
}


