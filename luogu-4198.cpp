#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e5 + 1;
constexpr double eps = 1e-8;
double ak[maxn];
struct SegmentTree {
  double maxv[maxn * 4];
  int len[maxn * 4];
#define lc (k * 2)
#define rc (lc + 1)
  int search(int k, int l, int r, double v) {
    // cerr << "search " << l << ' ' << r << ' ' << v << endl;
    if (l == r)
      return ak[l] - v > eps;
    const int mid = (l + r) / 2;
    if (maxv[lc] - v > eps)
      return search(lc, l, mid, v) + len[k] - len[lc];
    else
      return search(rc, mid + 1, r, v);
  }
  inline void maintain(int k, int l, int r) {
    const int mid = (l + r) / 2;
    len[k] = len[lc] + search(rc, mid + 1, r, maxv[lc]);
    maxv[k] = max(maxv[lc], maxv[rc]);
  }
  void modify(int k, int l, int r, int p) {
    if (l == r) {
      maxv[k] = ak[l];
      len[k] = 1;
    } else {
      const int mid = (l + r) / 2;
      if (p <= mid)
        modify(lc, l, mid, p);
      else
        modify(rc, mid + 1, r, p);
      maintain(k, l, r);
    }
  }
} segt;

int main() {
  int N, M;
  cin >> N >> M;
  for (int i = 1; i <= M; ++i) {
    int x, y;
    cin >> x >> y;
    ak[x] = double(y) / x;
    segt.modify(1, 1, N, x);
    cout << segt.len[1] << '\n';
  }
  return 0;
}
