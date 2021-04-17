#include <iostream>
#include <vector>
#include <stack>
#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 2e5 + 4, maxc = 5e4 + 4;
constexpr int mlg = 20;
vector<int> verts[maxn];
int fa[maxn][mlg];
int in[maxn], out[maxn];
int f[maxn][mlg], g[maxn][mlg];
stack<int> buck[maxn];
int W[maxn], Par1[maxn];
void dfs(int u, int la) {
  static int clk = 0;
  buck[W[u]].push(u);
  in[u] = ++clk;
  f[u][0] = buck[W[u] + 1].top();
  g[u][0] = buck[W[u] - 1].top();
  Par1[u] = buck[1].top();
  for (int i = 1; i < mlg; ++i) {
    fa[u][i] = fa[fa[u][i - 1]][i - 1];
    f[u][i] = f[f[u][i - 1]][i - 1];
    g[u][i] = g[g[u][i - 1]][i - 1];
  }
  for (int v : verts[u]) {
    if (v == la)
      continue;
    fa[v][0] = u;
    dfs(v, u);
  }
  buck[W[u]].pop();
  out[u] = clk;
}
inline bool intree(int x, int y) {
  return in[x] <= in[y] && out[x] >= in[y];
}
inline int getlca(int x, int y) {
  if (intree(x, y))
    return x;
  for (int i = mlg - 1; i >= 0; --i) {
    if (!intree(fa[x][i], y))
      x = fa[x][i];
  }
  return fa[x][0];
}
int P[maxc];
tuple<int, int, int> qry[maxn];
vector<int> ids[maxn];
int N, M, C;
void dfsans(int u, int la) {
  buck[W[u]].push(u);
  for (int c : ids[u]) {
    auto &[x, y, v] = qry[c];
    int L = v + 1, R = C, ans = v;
    while (L <= R) {
      const int mid = (L + R) / 2;
      int t = buck[mid].top();
      for (int i = mlg - 1; i >= 0; --i) {
        if (in[x] < in[g[t][i]])
          t = g[t][i];
      }
      if (in[x] < in[t] && W[t] <= v + 1) {
        L = mid + 1;
        ans = mid;
      } else {
        R = mid - 1;
      }
    }
    v = ans;
  }
  for (int v : verts[u]) {
    if (v == la)
      continue;
    dfsans(v, u);
  }
  buck[W[u]].pop();
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> N >> M >> C;
  out[0] = N + 1;
  for (int i = 1; i <= M; ++i) {
    int a;
    cin >> a;
    P[a] = i;
  }
  for (int i = 1; i <= N; ++i) {
    cin >> W[i];
    W[i] = P[W[i]];
  }
  for (int i = 0; i <= C + 1; ++i)
    buck[i].push(0);
  for (int i = 1; i < N; ++i) {
    int a, b;
    cin >> a >> b;
    verts[a].push_back(b);
    verts[b].push_back(a);
  }
  dfs(1, 0);
  int Q;
  cin >> Q;
  for (int i = 1; i <= Q; ++i) {
    auto &[x, y, v] = qry[i];
    cin >> x >> y;
    const int lca = getlca(x, y);
    x = Par1[x];
    for (int i = mlg - 1; i >= 0; --i) {
      if (in[lca] <= in[f[x][i]])
        x = f[x][i];
    }
    if (in[lca] <= in[x])
      v = W[x];
    else
      v = 0;
    ids[y].push_back(i);
    x = lca;
  }
  dfsans(1, 0);
  for (int i = 1; i <= Q; ++i) {
    cout << get<2>(qry[i]) << '\n';
  }
  return 0;
}
