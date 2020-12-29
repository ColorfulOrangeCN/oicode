#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 5e5 + 2;
int N, M, W;
struct SegmentTree {
  int minv[maxn * 4];
#define lc (k * 2)
#define rc (lc + 1)
  void modify(int k, int l, int r, int p, int v) {
    if (p == 0 || p > N)
      return;
    if (l == r) {
      minv[k] = v;
    } else {
      const int mid = (l + r) / 2;
      if (p <= mid)
        modify(lc, l, mid, p, v);
      else
        modify(rc, mid + 1, r, p, v);
      minv[k] = min(minv[lc], minv[rc]);
    }
  }
  int query(int k, int l, int r, int L, int R) {
    if (L <= l && r <= R)
      return minv[k];
    if (r < L || l > R)
      return 0x7fffffff;
    const int mid = (l + r) / 2;
    return min(query(lc, l, mid, L, R), query(rc, mid + 1, r, L, R));
  }
} segt;
set<int> st[maxn];
int a[maxn];
inline void adjust(int x) {
  if (!x)
    return;
  auto &cu = st[a[x]], &mi = st[W - a[x]];
  auto nit = cu.find(x), cit = nit++;
  auto p = *mi.upper_bound(*cit);
  if (p < *nit)
    segt.modify(1, 1, N, x, p);
  else
    segt.modify(1, 1, N, x, N + 1);
}
int main() {
  int cnt = 0;
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> N >> M >> W;
  copy_n(istream_iterator<int>(cin), N, a + 1);
  for (int i = 0; i <= W; ++i)
    st[i].insert(N + 1), st[i].insert(0);
  for (int i = 1; i <= N; ++i)
    st[a[i]].insert(i);
  for (int i = 1; i <= N; ++i)
    adjust(i);
  for (int i = 1; i <= M; ++i) {
    int opt, x, y;
    cin >> opt >> x >> y;
    if (opt == 1) {
      st[a[x]].erase(x);
      st[y].insert(x);
      swap(a[x], y);
      adjust(x);
      adjust(*--st[W - a[x]].lower_bound(x));
      adjust(*--st[W - y].lower_bound(x));
      adjust(*--st[y].upper_bound(x));
    } else if (opt == 2) {
      x ^= cnt;
      y ^= cnt;
      if (x > y) {
        cout << "No\n";
        continue;
      }
      int p = segt.query(1, 1, N, x, y);
      cnt += (p <= y);
      cout << (p <= y ? "Yes" : "No") << '\n';
    }
  }
  return 0;
}
