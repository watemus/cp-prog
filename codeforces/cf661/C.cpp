#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <deque>
#include <set>
#include <iterator>
#include <map>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <cmath>
#include <iomanip>
#include <unordered_map>

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")

using namespace std;

typedef long long ll;
typedef long double ld;
#define FOR(i, n) for ((i) = 0; (i) < (n); (i)++)
#define FOR_(i, n, t) for ((i) = 0; (i) < (n); (i) += (t))
#define all(a) (a).begin(), (a).end()
#define pb push_back
#define mp make_pair
const ll inf = 1e18;

vector <ll> w;
map <ll, ll> ms;
set <ll> r;

ll count_ans(ll x)
{
  ll ans = 0;
  ms.clear();
  for (ll u : w) ms[u]++;
  for (ll u : w)
  {
    ms[u]--;
    if (ms[x - u] > 0)
    {
      ans++;
      ms[x - u]--;
    }
  }
  return ans;
}

int main()
{
  freopen("input.txt", "r", stdin);
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  ll t, u, n, k, i, j;
  cin >> t;
  FOR(u, t)
  {
    cin >> n;
    w.resize(n);
    FOR(i, n) cin >> w[i];
    sort(all(w));
    ll m = 0;
    for (i = 0; i < n; i++)
      for (j = 0; j < i; j++)
        r.insert(w[i] + w[j]);
    for (ll z : r)
      m = max(m, count_ans(z));
    cout << m << '\n';
  }
  return 0;
}