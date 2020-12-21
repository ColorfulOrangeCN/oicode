#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e5 + 1;
typedef long long inte;
int P;
struct SegmentTree {
  struct Lazy {
    inte mul, sum;
    Lazy() : mul(1), sum(0) {}
  } lazy[maxn * 4];
  inte sum[maxn * 4];
#define lc (k * 2)
#define rc (lc + 1)
  inline void applyTo(Lazy b, Lazy &a) {
    (a.sum *= b.mul) %= P;
    (a.mul *= b.mul) %= P;
    (a.sum += b.sum) %= P;
  }
  void pushdown(int k, int l, int r) {
    if (l != r) {
      applyTo(lazy[k], lazy[lc]);
      applyTo(lazy[k], lazy[rc]);
    }
    // assert(lazy[k].mul);
    (sum[k] *= lazy[k].mul) %= P;
    (sum[k] += lazy[k].sum % P * (r - l + 1)) %= P;
    lazy[k] = Lazy();
  }
  void modify(int k, int l, int r, int L, int R, Lazy v) {
    pushdown(k, l, r);
    if (r < L || l > R)
      return;
    if (L <= l && r <= R) {
      lazy[k] = v;
      pushdown(k, l, r);
    } else {
      const int mid = (l + r) / 2;
      modify(lc, l, mid, L, R, v);
      modify(rc, mid + 1, r, L, R, v);
      sum[k] = (sum[lc] + sum[rc]) % P;
    }
    assert(lazy[k].mul == 1 && lazy[k].sum == 0);
  }
  inte query(int k, int l, int r, int L, int R) {
    if (r < L || l > R)
      return 0;
    pushdown(k, l, r);
    if (L <= l && r <= R) {
      return sum[k];
    } else {
      const int mid = (l + r) / 2;
      return (query(lc, l, mid, L, R) + query(rc, mid + 1, r, L, R)) % P;
    }
  }
} segt;
typedef SegmentTree::Lazy Option;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int N;
  cin >> N >> P;
  Option op;
  for (int i = 1; i <= N; ++i) {
    cin >> op.sum;
    segt.modify(1, 1, N, i, i, op);
  }
  int M;
  cin >> M;
  for (int i = 1; i <= M; ++i) {
    op = Option();
    int t, l, r;
    cin >> t >> l >> r;
    if (t == 1) {
      cin >> op.mul;
      segt.modify(1, 1, N, l, r, op);
    } else if (t == 2) {
      cin >> op.sum;
      segt.modify(1, 1, N, l, r, op);
    } else {
      cout << segt.query(1, 1, N, l, r) << '\n';
    }
  }
  return 0;
}
