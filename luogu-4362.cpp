#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 305;
int f[maxn][maxn][2], t[maxn][2], sz[maxn];
int N, M, K;
vector<pair<int, int>> verts[maxn];
inline int& letmin(int& l, int r) {
  return l > r ? (l = r) : l;
}
void dfs(int u, int la) {
  sz[u] = 1;
  f[u][0][0] = f[u][1][1] = 0;
  for (auto [v, c] : verts[u]) {
    if (v == la)
      continue;
    memset(t, 0x3f, sizeof(t));
    dfs(v, u);
    sz[u] += sz[v];
    for (int i = 0; i <= min(K, sz[u]); ++i) {
      for (int j = 0; j <= min(i, sz[v]); ++j) {
        letmin(t[i][0], f[u][i - j][0] + min(f[v][j][0] + (M == 2 ? c : 0), f[v][j][1]));
        letmin(t[i][1], f[u][i - j][1] + min(f[v][j][1] + c, f[v][j][0]));
      }
    }
    memcpy(f[u], t, sizeof(t));
  }
}
int main() {
  cin >> N >> M >> K;
  for (int i = 1; i < N; ++i) {
    int a, b, c;
    cin >> a >> b >> c;
    verts[a].push_back(make_pair(b, c));
    verts[b].push_back(make_pair(a, c));
  }
  memset(f, 0x3f, sizeof(f));
  dfs(1, 0);
  if (M + K > N + 1)
    cout << -1 << endl;
  else
    cout << f[1][K][1] << endl;
  return 0;
}
