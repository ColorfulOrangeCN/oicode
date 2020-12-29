#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e5 + 1;
struct SegmentTree {
  struct Node {
    double x, x2;
  } nodes[maxn * 4];
  double lazy[maxn * 4];
  Node nadd(Node x, double v, int cnt) {
    return Node{x.x + v * cnt, x.x2 + 2 * x.x * v + v * v * cnt};
  }
#define lc (k * 2)
#define rc (lc + 1)
  void pushdown(int k, int l, int r) {
    if (l != r) {
      lazy[lc] += lazy[k];
      lazy[rc] += lazy[k];
    }
    nodes[k] = nadd(nodes[k], lazy[k], r - l + 1);
    lazy[k] = 0;
  }
  void modify(int k, int l, int r, int L, int R, double v) {
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
      nodes[k].x = nodes[lc].x + nodes[rc].x;
      nodes[k].x2 = nodes[lc].x2 + nodes[rc].x2;
    }
  }
  Node query(int k, int l, int r, int L, int R) {
    if (r < L || l > R)
      return Node{0, 0};
    pushdown(k, l, r);
    if (L <= l && r <= R) {
      return nodes[k];
    } else {
      const int mid = (l + r) / 2;
      Node a = query(lc, l, mid, L, R), b = query(rc, mid + 1, r, L, R);
      return Node{a.x + b.x, a.x2 + b.x2};
    }
  }
} segt;
typedef SegmentTree::Node Option;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int N, M;
  cin >> N >> M;
  for (int i = 1; i <= N; ++i) {
    double x;
    cin >> x;
    segt.modify(1, 1, N, i, i, x);
  }
  cout << fixed;
  for (int i = 1; i <= M; ++i) {
    int op, l, r;
    cin >> op >> l >> r;
    if (op == 1) {
      double x;
      cin >> x;
      segt.modify(1, 1, N, l, r, x);
    } else if (op == 2) {
      cout << setprecision(4) << segt.query(1, 1, N, l, r).x / (r - l + 1) << '\n';
    } else {
      Option t = segt.query(1, 1, N, l, r);
      cout << setprecision(4) << segt.nadd(t, -t.x / (r - l + 1), (r - l + 1)).x2 / (r - l + 1) << '\n';
    }
  }
  return 0;
}
