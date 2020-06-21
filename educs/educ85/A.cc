#include <bits/stdc++.h>

//#define FAST_ALLOC

#ifdef FAST_ALLOC
constexpr int MEM_SIZE = 2e8;
char mem[MEM_SIZE];
char *cur = mem;

void* operator new(size_t n) {
  char* ans = cur;
  cur += n;
  return ans;
}

void operator delete(void *p) {}
#endif

using namespace std;

using ll = long long;

#define int ll
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define ff first
#define ss second

constexpr int MOD = 1e9 + 7;

struct segtree {
    int l, r, m;
    segtree *lt, *rt;
    pair<int, int> val = {0, 0};
    pair<int, int> mrg(pair<int, int> a, pair<int, int> b) {
        pair<int, int> ans;
        if (a.ff > b.ff) {
            ans = a;
        } else if (b.ff > a.ff) {
            ans = b;
        } else {
            ans = a;
            ans.ss += b.ss;
            ans.ss %= MOD;
        }
        return ans;
    }
    segtree(int l, int r)
            : l(l), r(r), m(l + r >> 1) {
        if (l + 1 < r) {
            lt = new segtree(l, m);
            rt = new segtree(m, r);
        }
    }
    void add(int at, pair<int, int> nval) {
        if (l + 1 == r) {
            val = mrg(nval, val);
        } else {
            if (at < m) lt->add(at, nval);
            else rt->add(at, nval);
            val = mrg(lt->val, rt->val);
        }
    }
    pair<int, int> get(int tl, int tr) {
        if (tl <= l && r <= tr) {
            return val;
        }
        pair<int, int> ans;
        if (tl < m) ans = mrg(ans, lt->get(tl, tr));
        if (m < tr) ans = mrg(ans, rt->get(tl, tr));
        return ans;
    }
};

void run() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> coord(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        coord[i] = a[i];
    }
    sort(all(coord));
    coord.resize(unique(all(coord)) - coord.begin());
    map<int, int> to;
    for (int i = 0; i < coord.size(); i++) {
        to[coord[i]] = i;
    }
    segtree t(0, coord.size());
    for (int i = 0; i < n; i++) {
        a[i] = to[a[i]];
        if (a[i] == 0) {
            t.add(0, {1, 1});
        } else {
            auto gt = t.get(0, a[i]);
            gt.ff++;
            gt.ss = max(1LL, gt.ss);
            t.add(a[i], gt);
        }
    }
    cout << t.get(0, coord.size()).ss;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    run();
    return 0;
}