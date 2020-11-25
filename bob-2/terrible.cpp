#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 3001, maxm = maxn * maxn, lgn = 25;
typedef long long inte;
int N, M;
struct Edge {
  int u, v, c, w, inMST, id;
} edges[maxm];
list<int> verts[maxn];
inline void buildEdge(int eid) {
  verts[edges[eid].u].push_back(eid);
  verts[edges[eid].v].push_back(eid);
}
inline bool operator < (const Edge &a, const Edge &b)
{ return a.c < b.c; }
typedef typename list<int>::iterator EPtr;
#define pVert(u, eid) (edges[eid].u == u ? edges[eid].v : edges[eid].u)

namespace mst {
  int par[maxn], ans = 0;
  int getPar(int x) {
    if (par[x] == x)
      return x;
    else
      return par[x] = getPar(par[x]);
  }
  bool compid(const Edge& a, const Edge& b) {
    return a.id < b.id;
  }
  Edge rest[maxn];
  int rtot = 0;
  void genMST() {
    sort(edges + 1, edges + M + 1);
    for (int i = 1; i <= N; ++i)
      par[i] = i;
    for (int i = 1; i <= M; ++i) {
      const int u = getPar(edges[i].u), v = getPar(edges[i].v);
      if (u != v) {
        par[u] = v;
        ans += edges[i].c;
        edges[i].inMST = true;
      } else {
        rest[rtot++] = edges[i];
      }
    }
    sort(edges + 1, edges + M + 1, compid);
  }
}

namespace hc {
  struct Node {
    int dep, size, hson, top, dfn, par;
  } nodes[maxn];
  int st[maxn][lgn];
  void predfs(int u) {
    nodes[u].size = 1;
    nodes[u].dep = nodes[nodes[u].par].dep + 1;
    for (int eid : verts[u]) {
      const int v = pVert(u, eid);
      if (v == nodes[u].par)
        continue;
      nodes[v].par = u;
      predfs(v);
      nodes[u].size += nodes[v].size;
      if (nodes[nodes[u].hson].size < nodes[u].size)
        nodes[u].hson = v;
    }
  }
  void initHC(int u) {
    if (nodes[u].hson) {
      nodes[nodes[u].hson].top = nodes[u].top;
      initHC(nodes[u].hson);
    }
    for (int eid : verts[u]) {
      const int v = pVert(u, eid);
      if (v == nodes[u].par || v == nodes[u].hson)
        continue;
      nodes[v].top = v;
      initHC(v);
    }
  }
}

int main() {
  cin >> N >> M;
  for (int i = 1; i <= M; ++i)
    cin >> edges[i].u >> edges[i].v >> edges[i].w, edges[i].id = i;
  return 0;
}
