#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 2e5 + 1, mods = 1e9 + 7;
typedef long long inte;
typedef pair<double, inte> Meta;
Meta w[maxn];
Meta f[maxn][2];
vector<int> verts[maxn];
Meta operator + (const Meta& a, const Meta& b) {
  return Meta(a.first + b.first, a.second * b.second % mods);
}
void dfs(int u, int la) {
  f[u][1] = w[u];
  f[u][0] = Meta(0, 1);
  for (int v : verts[u]) {
    if (v == la)
      continue;
    dfs(v, u);
    f[u][0] = f[u][0] + max(f[v][1], f[v][0]);
    f[u][1] = f[u][1] + f[v][0];
  }
}
int main() {
  int N;
  cin >> N;
  for (int i = 1; i <= N; ++i) {
    cin >> w[i].second;
    w[i].first = log2(w[i].second);
  }
  for (int i = 1; i < N; ++i) {
    int a, b;
    cin >> a >> b;
    verts[a].push_back(b);
    verts[b].push_back(a);
  }
  dfs(1, 0);
  cout << max(f[1][0], f[1][1]).second << endl;
  return 0;
}
