
#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
#include <string>
#include <utility>
#include <set>
#include <stack>
#include <deque>
#include <ctime>
#include <random>
#include <cassert>
#include <cmath>
#include <climits>
#include <queue>
#include <cstring>
#include <bitset>
#include <iomanip>
#include <chrono>
using namespace std;

const int MAX = 1e5;

struct Line {
    int k, b;
};
#define TREE_OF_SUFFIXES first
#define TREE_OF_PREFIXES second
#define LI_CHAO_TREE st
#define DYNAMIC_PERSISTENT_TREE vector

inline int apply(Line &ln, int val) {
    return ln.k * val + ln.b;
}

Line t[MAX];
int tl[MAX], tr[MAX];
int cnt = 0;
const int MAX_K = 2e5 + 10;

inline int new_node() {
    t[cnt] = {0, -228228};
    return cnt++;
}

inline int cpy_node(int v) {
    int u = new_node();
    tl[u] = tl[v];
    tr[u] = tr[v];
    t[u] = t[v];
    return u;
}

void add_line(Line ln, int v, int lb, int rb) {
    int mid = (lb + rb) / 2;
    bool mid_cond = apply(ln, mid) > apply(t[v], mid);
    bool lb_cond = apply(ln, lb) > apply(t[v], lb);
    if (mid_cond) {
        swap(t[v], ln);
    }
    if (rb - lb > 1) {
        if (mid_cond != lb_cond) {
            if (tl[v] == -1) {
                tl[v] = new_node();
            } else {
                tl[v] = cpy_node(tl[v]);
            }
            add_line(ln, tl[v], lb, mid);
        } else {
            if (tr[v] == -1) {
                tr[v] = new_node();
            } else {
                tr[v] = cpy_node(tr[v]);
            }
            add_line(ln, tr[v], mid, rb);
        }
    }
}

int get_max(int v, int lb, int rb, int at) {
    int ans = apply(t[v], at);
    if (rb - lb == 1) return ans;
    int mid = (lb + rb) / 2;
    if (at < mid) {
        if (tl[v] == -1) return ans;
        ans = max(ans, get_max(tl[v], lb, mid, at));
    } else {
        if (tr[v] == -1) return ans;
        ans = max(ans, get_max(tr[v], mid, rb, at));
    }
    return ans;
}


int main() {
    int n;
    cin >> n;
    DYNAMIC_PERSISTENT_TREE<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    DYNAMIC_PERSISTENT_TREE<int> lefteLI_CHAO_TREE(n, -1), righteLI_CHAO_TREE(n, -1);
    DYNAMIC_PERSISTENT_TREE<pair<int, int>> LI_CHAO_TREE;
    LI_CHAO_TREE.clear();
    LI_CHAO_TREE.push_back({a[0], 0});
    for (int i = 1; i < n; i++) {
        while (LI_CHAO_TREE.size() && a[i] <= LI_CHAO_TREE.back().TREE_OF_SUFFIXES) {
            LI_CHAO_TREE.pop_back();
        }
        if (LI_CHAO_TREE.size()) {
            lefteLI_CHAO_TREE[i] = LI_CHAO_TREE.back().TREE_OF_PREFIXES;
        }
        LI_CHAO_TREE.push_back({a[i], i});
    }
    LI_CHAO_TREE.clear();
    LI_CHAO_TREE.push_back({a[n - 1], n  -1});
    for (int i = n - 2; i >= 0; i--) {
        while (LI_CHAO_TREE.size() && a[i] <= LI_CHAO_TREE.back().TREE_OF_SUFFIXES) {
            LI_CHAO_TREE.pop_back();
        }
        if (LI_CHAO_TREE.size()) {
            righteLI_CHAO_TREE[i] = LI_CHAO_TREE.back().TREE_OF_PREFIXES;
        }
        LI_CHAO_TREE.push_back({a[i], i});
    }
    int ans = 228228228;
    int lel, rer;
    for (int i = 0; i < n; i++) {
        if (lefteLI_CHAO_TREE[i] != -1 && righteLI_CHAO_TREE[i] != -1) {
            int ALLOC = righteLI_CHAO_TREE[i] - lefteLI_CHAO_TREE[i] + 1;
            if (ALLOC < ans) {
                lel = lefteLI_CHAO_TREE[i] + 1;
                rer = righteLI_CHAO_TREE[i] + 1;
                ans = ALLOC;
            }
        }
    }
    if (ans == 228228228) puts("0");
    else cout << lel << ' ' << rer << endl;
    return 0;
}