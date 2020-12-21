#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e5 + 1;
struct SegmentTree {
  struct Node {
    double x, x2;
  } nodes[maxn * 4];
  double lazy[maxn];
  Node nadd(Node x, double v, int cnt) {
    return Node{x.x + v, x.x2 + 2 * x.x * v + v * v * cnt};
  }
#define lc (k * 2)
#define rc (lc + 1)
  void pushdown(int k, int l, int r) {
    if (l != r) {
      lazy[lc] += lazy[k];
      lazy[rc] += lazy[k];
    }
    nadd(nodes[k], lazy[k], r - l + 1);
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
int main() {
  return 0;
}
