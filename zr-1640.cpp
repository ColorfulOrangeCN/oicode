#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e6 + 1;
typedef long long inte;
struct SegmentTree {
  struct Node {
    inte lazy, maxv;
  } nodes[maxn * 4];
#define lc (k * 2)
#define rc (lc + 1)
  void add(int k, int l, int r, int L, int R, inte v) {
    if (l > R || r < L)
      return;
    if (L <= l && r <= R) {
      nodes[k].lazy += v;
    } else {
      const int mid = (l + r) / 2;
      add(lc, l, mid, L, R, v);
      add(rc, mid + 1, r, L, R, v);
    }
    if (l != r)
      nodes[k].maxv = max(nodes[lc].maxv, nodes[rc].maxv);
    else
      nodes[k].maxv = 0;
    nodes[k].maxv += nodes[k].lazy;
  }
  inte query() {return nodes[1].maxv;}
} segt;
int la[maxn], lla[maxn], c[maxn];
inte d[maxn];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int N, M;
  cin >> N >> M;
  inte ans = 0;
  copy_n(istream_iterator<int>(cin), N, c + 1);
  copy_n(istream_iterator<inte>(cin), M, d + 1);
  for (int i = 1; i <= N; ++i) {
    // if (la[c[i]])
      segt.add(1, 1, N, la[c[i]] + 1, i, d[c[i]]);
    if (la[c[i]])
      segt.add(1, 1, N, lla[c[i]] + 1, la[c[i]], -d[c[i]]);
    lla[c[i]] = la[c[i]];
    la[c[i]] = i;
    ans = max(ans, segt.query());
    // cerr << i << ' ' << segt.query() << endl;
  }
  cout << ans << endl;
  return 0;
}
