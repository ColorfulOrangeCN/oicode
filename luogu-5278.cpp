#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long HashType;
constexpr int maxn = 3e5 + 2;
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
      nodes[k].x2 = HashType(v) * v;
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
    if (r < L || l > R) {
      return Node{0, 0xffffffffffffffffll, 0};
    } else {
      const int mid = (l + r) / 2;
      return add(query(lc, l, mid, L, R), query(rc, mid + 1, r, L, R));
    }
  }
} segt;
inline HashType p2 (HashType v) {return v * v;}
int main() {
  cerr << sizeof(segt) / 1024 / 1024 << endl;
  ios::sync_with_stdio(false);
  cin.tie(0);
  int N, M;
  cin >> N >> M;
  for (int i = 1; i <= N; ++i) {
    int a;
    cin >> a;
    segt.modify(1, 1, N, i, a);
  }
  int cnt = 0;
  for (int i = 1; i <= M; ++i) {
    int opt, a, b;
    cin >> opt >> a >> b;
    a ^= cnt;
    b ^= cnt;
    if (opt == 1) {
      segt.modify(1, 1, N, a, b);
    } else {
      int k;
      cin >> k;
      k ^= cnt;
      auto t = segt.query(1, 1, N, a, b);
      bool flag = true;
      const int len = b - a + 1;
      flag &= (t.maxv == t.minv + k * (len - 1));
      HashType ans = len * p2(t.minv) + k * t.minv * len * (len - 1) + len * (len - 1) * (2 * len - 1) / 6 * p2(k);
      flag &= (ans == t.x2);
      cout << (flag ? "Yes" : "No") << '\n';
      cnt += flag;
    }
  }
  return 0;
}

