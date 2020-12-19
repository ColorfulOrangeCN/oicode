#define NDEBUG
#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 2.5e5 + 1;
int N, Q;
typedef unsigned long HashType;
struct BIT {
  HashType c[maxn];
  inline int lowbit(int x) {
    return x & -x;
  }
  void xorv(int x, HashType v) {
    while (x <= N) {
      c[x] ^= v;
      x += lowbit(x);
    }
  }
  HashType query(int l, int r) {
    --l;
    HashType res = 0;
    while (r > l) {
      res ^= c[r];
      r -= lowbit(r);
    }
    while (l > r) {
      res ^= c[l];
      l -= lowbit(l);
    }
    return res;
  }
  void clear() {
    fill(c, c + N + 1, 0);
  }
} bt;
struct Node {
  int dep, size, top, hson, dfn, par;
} nodes[maxn];
vector<int> verts[maxn];
void predfs(int u) {
  nodes[u].size = 1;
  nodes[u].hson = 0;
  for (int v : verts[u]) {
    if (v == nodes[u].par)
      continue;
    nodes[v].par = u;
    nodes[v].dep = nodes[u].dep + 1;
    predfs(v);
    nodes[u].size += nodes[v].size;
    if (nodes[nodes[u].hson].size < nodes[v].size)
      nodes[u].hson = v;
  }
}
int clk = 0;
void initHC(int u) {
  nodes[u].dfn = ++clk;
  if (nodes[u].hson) {
    nodes[nodes[u].hson].top = nodes[u].top;
    initHC(nodes[u].hson);
  }
  for (int v : verts[u]) {
    if (v == nodes[u].par || v == nodes[u].hson)
      continue;
    nodes[v].top = v;
    initHC(v);
  }
}
pair<HashType, int> getXor(int x, int y) {
  HashType res = 0;
  while (nodes[x].top != nodes[y].top) {
    if (nodes[nodes[x].top].dep < nodes[nodes[y].top].dep)
      swap(x, y);
    res ^= bt.query(nodes[nodes[x].top].dfn, nodes[x].dfn);
    x = nodes[nodes[x].top].par;
  }
  if (nodes[x].dep > nodes[y].dep)
    swap(x, y);
  res ^= bt.query(nodes[x].dfn, nodes[y].dfn);
  return make_pair(res, x);
}
HashType bs[maxn];
constexpr HashType base = 19491001;
int A[maxn];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    clk = 0;
    bt.clear();
    cin >> N >> Q;
    copy_n(istream_iterator<int>(cin), N, A + 1);
    for (int i = 1; i <= N; ++i)
      bs[i] = bs[i - 1] ^ (i * base);
    for (int i = 1; i <= N; ++i)
      verts[i].clear();
    for (int i = 1; i < N; ++i) {
      int a, b;
      cin >> a >> b;
      verts[a].push_back(b);
      verts[b].push_back(a);
    }
    nodes[1].dep = nodes[1].top = 1;
    predfs(1);
    initHC(1);
    for (int i = 1; i <= N; ++i)
      bt.xorv(nodes[i].dfn, A[i] * base);
    for (int i = 0; i < Q; ++i) {
      int tp, x, y;
      cin >> tp >> x >> y;
      if (tp == 1) {
        pair<HashType, int> res = getXor(x, y);
        if (res.first == bs[nodes[x].dep + nodes[y].dep - 2 * nodes[res.second].dep + 1])
          cout << "Yes\n";
        else
          cout << "No\n";
      } else {
        bt.xorv(nodes[x].dfn, (A[x] * base) ^ (y * base));
        A[x] = y;
      }
    }
    
  }
  return 0;
}
