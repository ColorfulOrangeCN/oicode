#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e5 + 4, maxm = 2e5 + 4;
struct Edge {
  int v, nxt, vis;
} edges[maxm * 4];
int newp = 1, head[maxn];
inline void addEdge(int u, int v) {
  edges[++newp].v = v;
  edges[newp].nxt = head[u];
  head[u] = newp;
}
int cnt = 0;
void dfs(int u) {
  for (int &i = head[u]; i; i = edges[i].nxt) {
    if (edges[i].vis)
      continue;
    edges[i].vis = edges[i ^ 1].vis = true;
    const int v = edges[i].v;
    dfs(v);
    if ((++cnt) & 1)
      cout << u << ' ' << v << '\n';
    else
      cout << v << ' ' << u << '\n';
  }
}
int d[maxn];
int main() {
  int N, M;
  cin >> N >> M;
  for (int i = 0, u, v; i < M; ++i) {
    cin >> u >> v;
    ++d[u];
    ++d[v];
    addEdge(u, v);
    addEdge(v, u);
  }
  vector<int> dv;
  for (int i = 1; i <= N; ++i)
    if (d[i] & 1)
      dv.push_back(i);
  for (int i = 0; i < dv.size(); i += 2) {
    addEdge(dv[i], dv[i + 1]);
    addEdge(dv[i + 1], dv[i]);
    ++M;
  }
  if (M & 1) {
    addEdge(1, 1);
    addEdge(1, 1);
    ++M;
  }
  cout << M << '\n';
  dfs(1);
  return 0;
}
