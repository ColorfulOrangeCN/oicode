#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e5 + 4;
vector<pair<int, int> > verts[maxn];
int f[maxn][2], g[maxn], h[maxn], nxt[maxn], tg[maxn];
void dfs(int u, int la) {
  for (auto [v, d] : verts[u]) {
    if (v == la)
      continue;
    dfs(v, u);
    if (f[v][0] + d > f[u][0]) {
      f[u][1] = f[u][0];
      f[u][0] = f[v][0] + d;
    } else if (f[u][1] < f[v][0] + d)
      f[u][1] = f[v][0] + d;
  }
  f[u][0] = max(f[u][0], 0);
}
void upd(int u, int la) {
  for (auto [v, d] : verts[u]) {
    if (v == la)
      continue;
    h[v] = h[u] + d;
    if (f[u][0] == f[v][0] + d)
      h[v] = max(f[u][1] + d, h[v]);
    else
      h[v] = max(f[u][0] + d, h[v]);
    upd(v, u);
  }
  g[u] = max(f[u][0], h[u]);
}
int L;
int ans = 0;
void tag(int u, int la, int way) {
  while (g[u] - g[nxt[way]] > L)
    way = nxt[way];
  --tg[way];
  ++tg[u];
  for (auto [v, d] : verts[u]) {
    if (v == la)
      continue;
    assert(g[v] >= g[u]);
    nxt[u] = v;
    tag(v, u, way);
    tg[u] += tg[v];
  }
  // cerr << u << ' ' << g[u] << ' ' << way << ' ' << f[u][1] << endl;
  ans = max(ans, tg[u]);
}
int main() {
  int N;
  cin >> N;
  for (int i = 1; i < N; ++i) {
    int a, b, c;
    cin >> a >> b >> c;
    verts[a].push_back(make_pair(b, c));
    verts[b].push_back(make_pair(a, c));
  }
  memset(f, -0x3f, sizeof(f));
  dfs(1, 0);
  upd(1, 0);
  nxt[0] = 1;
  for (int i = 2; i <= N; ++i) {
    if (g[i] < g[nxt[0]])
      nxt[0] = i;
  }
  // cerr << nxt[0] << endl;
  int Q;
  cin >> Q;
  for (int i = 1; i <= Q; ++i) {
    cin >> L;
    memset(tg, 0, sizeof(tg));
    ans = 0;
    tag(nxt[0], 0, 0);
    cout << ans << endl;
  }
  return 0;
}
