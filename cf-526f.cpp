#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 3e5 + 4;
struct SegmentTree {
  struct Node {
    int minv, mcnt, adv;
  } nodes[maxn * 4];
#define lc (k * 2)
#define rc (lc + 1)
  inline void build(int k, int l, int r) {
    nodes[k].mcnt = r - l + 1;
    if (l != r) {
      const int mid = (l + r) / 2;
      build(lc, l, mid);
      build(rc, mid + 1, r);
    }
  }
  inline void add(int k, int l, int r, int L, int R, int v) {
    if (r < L || R < l)
      return;
    if (L <= l && r <= R) {
      nodes[k].adv += v;
      nodes[k].minv += v;
    } else {
      const int mid = (l + r) / 2;
      add(lc, l, mid, L, R, v);
      add(rc, mid + 1, r, L, R, v);
      nodes[k].minv = min(nodes[lc].minv, nodes[rc].minv);
      nodes[k].mcnt = 0;
      if (nodes[lc].minv == nodes[k].minv)
        nodes[k].mcnt += nodes[lc].mcnt;
      if (nodes[rc].minv == nodes[k].minv)
        nodes[k].mcnt += nodes[rc].mcnt;
      nodes[k].minv += nodes[k].adv;
    }
  }
} segt;
int chs[maxn];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int N;
  cin >> N;
  for (int i = 1; i <= N; ++i) {
    int a, b;
    cin >> a >> b;
    chs[a] = b;
  }
  segt.build(1, 1, N);
  stack<pair<int, int> > smax, smin;
  smax.push(make_pair(N + 1, 0));
  smin.push(make_pair(-1, 0));
  long long ans = 0;
  for (int i = 1; i <= N; ++i) {
    segt.add(1, 1, N, 1, i, -1);
    int la = i, lv = chs[i];
    while (!smax.empty() && smax.top().first <= chs[i]) {
      segt.add(1, 1, N, smax.top().second + 1, la, chs[i] - lv);
      la = smax.top().second;
      lv = smax.top().first;
      smax.pop();
    }
    segt.add(1, 1, N, smax.top().second + 1, la, chs[i] - lv);
    smax.push(make_pair(chs[i], i));
    while (!smin.empty() && smin.top().first >= chs[i]) {
      segt.add(1, 1, N, smin.top().second + 1, la, -chs[i] + lv);
      la = smin.top().second;
      lv = smin.top().first;
      smin.pop();
    }
    segt.add(1, 1, N, smin.top().second + 1, la, -chs[i] + lv);
    smin.push(make_pair(chs[i], i));
    ans += segt.nodes[1].mcnt;
  }
  cout << ans << endl;
  return 0;
}
