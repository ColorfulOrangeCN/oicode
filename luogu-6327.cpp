#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 2e5 + 1;
typedef complex<double> Number;
Number a[maxn];
struct SegmentTree{
  Number sum[maxn * 4], lazy[maxn * 4];
#define lc (k * 2)
#define rc (lc + 1)
  void build(int k, int l, int r) {
    if (l == r) {
      sum[k] = a[l];
      lazy[k] = a[l];
    } else {
      const int mid = (l + r) / 2;
      build(lc, l, mid);
      build(rc, mid + 1, r);
      sum[k] = sum[lc] + sum[rc];
      lazy[k] = Number(1, 0);
    }
  }
  void update(int k, int l, int r, int L, int R, Number v) {
    if (r < L || l > R)
      return;
    if (L <= l && r <= R) {
      lazy[k] *= v;
    } else {
      const int mid = (l + r) / 2;
      update(lc, l, mid, L, R, v);
      update(rc, mid + 1, r, L, R, v);
    }
    if (l != r)
      sum[k] = sum[lc] + sum[rc];
    else
      sum[k] = Number(1, 0);
    sum[k] *= lazy[k];
  }
  Number query(int k, int l, int r, int L, int R) {
    if (r < L || l > R)
      return Number(0, 0);
    if (L <= l && r <= R) {
      // cerr << sum[k] << endl;
      return sum[k];
    } else {
      const int mid = (l + r) / 2;
      return (query(lc, l, mid, L, R) + query(rc, mid + 1, r, L, R)) * lazy[k];
    }
  }
} segt;
inline Number ei(double x) {
  return Number(cos(x), sin(x));
}
int main() {
  int N;
  cin >> N;
  for (int i = 1; i <= N; ++i) {
    int x;
    cin >> x;
    a[i] = ei(x);
  }
  cerr << (ei(1) * ei(1)).imag() << endl;
  segt.build(1, 1, N);
  int M;
  cin >> M;
  for (int i = 1; i <= M; ++i) {
    int op, l, r;
    cin >> op >> l >> r;
    if (op == 1) {
      int x;
      cin >> x;
      segt.update(1, 1, N, l, r, ei(x));
    } else {
      cout << fixed << setprecision(1) << segt.query(1, 1, N, l, r).imag() << '\n';
    }
  }
  return 0;
}
