#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e5 + 1, lgv = 32, maxv = 1e9;
typedef long long inte;
struct SegmentTree {
  struct Node {
    int csum;
    inte vsum;
    int l, r;
  } nodes[maxn * lgv];
  int newp;
  void update(int k, int l, int r, int p, int v) {
    if (l == r) {
      nodes[k].csum += v;
      nodes[k].vsum = inte(nodes[k].csum) * l;
      return;
    }
    const int mid = (l + r) / 2;
    if (p <= mid) {
      if (!nodes[k].l)
        nodes[k].l = ++newp;
      update(nodes[k].l, l, mid, p, v);
    } else {
      if (!nodes[k].r)
        nodes[k].r = ++newp;
      update(nodes[k].r, mid + 1, r, p, v);
    }
    nodes[k].csum = nodes[nodes[k].l].csum + nodes[nodes[k].r].csum;
    nodes[k].vsum = nodes[nodes[k].l].vsum + nodes[nodes[k].r].vsum;
  }
  double bound(int k, int l, int r, double v) {
    if (!k)
      return 0;
    if (l == r) {
      if (l <= v)
        return nodes[k].csum * v - nodes[k].vsum;
      return 0;
    }
       const int mid = (l + r) / 2;
    if (mid <= v)
      return nodes[nodes[k].l].csum * v - nodes[nodes[k].l].vsum + bound(nodes[k].r, mid + 1, r, v);
    else
      return bound(nodes[k].l, l, mid, v);
  }
} segt;
int N, Q;
int p[maxn];
int main() {
  cin >> N >> Q;
  segt.newp = 1;
  for (int i = 1; i <= N; ++i) {
    cin >> p[i];
    segt.update(1, 0, maxv, p[i], 1);
  }
  cout << fixed;
  for (int i = 0; i < Q; ++i) {
    int op;
    cin >> op;
    if (op == 1) {
      int a, b;
      cin >> a >> b;
      segt.update(1, 0, maxv, p[a], -1);
      segt.update(1, 0, maxv, p[a] = b, 1);
    } else {
      double v;
      cin >> v;
      double L = 0, R = 1e24;
      while (abs(R - L) > 0.5e-4) {
        const double mid = (L + R) / 2;
        // cerr << mid << ' ' << segt.bound(1, 0, maxv, mid) << endl;
        if (segt.bound(1, 0, maxv, mid) >= v)
          R = mid;
        else
          L = mid;
      }
      cout << L << endl;
    }
  }
  return 0;
}
