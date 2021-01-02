#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e5 + 5;
typedef long long inte;
int N, a[maxn];
struct BIT {
  inte c[maxn];
  inline int lowbit(int x) { return x & -x; }
  void build() {
    for (int i = 1; i <= N; ++i) {
      cin >> a[i];
      c[i] = a[i];
      for (int j = 1; j < lowbit(i); j *= 2)
        c[i] += c[i - j];
    }
  }
  void add(int x, int v) {
    while (x <= N) {
      c[x] += v;
      x += lowbit(x);
    }
  }
  inte query(int l, int r) {
    --l;
    inte res = 0;
    while (r > l)
      res += c[r], r -= lowbit(r);
    while (l > r)
      res -= c[l], l -= lowbit(l);
    return res;
  }
  
} bt;
set<int> plc[5 * maxn];
int main(int argc, char *argv[])
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  int M;
  cin >> N >> M;
  bt.build();
  for (int i = 1; i <= N; ++i) {
    plc[a[i]].insert(i);
    for (int j = 2; j * j <= a[i]; ++j) {
      if (a[i] % j == 0) {
        plc[j].insert(i);
        if (j * j != a[i])
          plc[a[i] / j].insert(i);
      }
    }
  }
  inte lastans = 0;
  while (M--) {
    inte op, l, r;
    cin >> op >> l >> r;
    l ^= lastans;
    r ^= lastans;
    if (op == 1) {
      inte x;
      cin >> x;
      x ^= lastans;
      auto it = plc[x].lower_bound(l), itr = plc[x].upper_bound(r);
      while (it != itr) {
        if (a[*it] % x) {
          plc[x].erase(it++);
        } else {
          bt.add(*it, a[*it] / x - a[*it]);
          a[*it] /= x;
          if (a[*it] % x)
            plc[x].erase(it++);
          else
            ++it;
        }
      }
    } else {
      cout << (lastans = bt.query(l, r)) << '\n';
    }
  }
  return 0;
}
