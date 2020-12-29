#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long HashType;
constexpr int maxn = 5e5 + 2;
struct SegmentTree {
  struct Node {
    HashType maxv, minv, x2;
  } nodes[maxn * 4];
  Node add(const Node& a, const Node& b) {
    return Node{max(a.maxv, b.maxv), min(a.minv, b.minv), a.x2 + b.x2};
  }
#define lc (k * 2)
#define rc (lc + 1)
  void modify(int k, int l, int r, int p, int v) {
    if (l == r) {
      nodes[k].maxv = nodes[k].minv = v;
      nodes[k].x2 = HashType(v) * v * v;
    } else {
      const int mid = (l + r) / 2;
      if (p <= mid)
        modify(lc, l, mid, p, v);
      else
        modify(rc, mid + 1, r, p, v);
      nodes[k] = add(nodes[lc], nodes[rc]);
    }
  }
  Node query(int k, int l, int r, int L, int R) {
    if (L <= l && r <= R)
      return nodes[k];
    const int mid = (l + r) / 2;
    if (mid >= R)
      return query(lc, l, mid, L, R);
    else if (mid < L)
      return query(rc, mid + 1, r, L, R);
    return add(query(lc, l, mid, L, R), query(rc, mid + 1, r, L, R));
  }
} segt;
inline HashType p2 (HashType v) {return v * v;}
HashType calc(int x) {
  return p2(x * HashType(x + 1) / 2);
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int N, M;
  cin >> N >> M;
  for (int i = 1; i <= N; ++i) {
    int a;
    cin >> a;
    segt.modify(1, 1, N, i, a);
  }
  for (int i = 1; i <= M; ++i) {
    int opt, a, b;
    cin >> opt >> a >> b;
    if (opt == 1) {
      segt.modify(1, 1, N, a, b);
    } else {
      auto t = segt.query(1, 1, N, a, b);
      if (t.x2 == calc(t.maxv) - calc(t.minv - 1))
        cout << "damushen" << '\n';
      else
        cout << "yuanxing" << '\n';
    }
  }
  return 0;
}
