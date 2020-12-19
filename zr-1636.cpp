#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e6 + 1;
vector<int> verts[maxn];
int f[maxn][2];
void dfs(int u, int dep) {
  for (int v : verts[u]) {
    dfs(v, dep + 1);
    f[u][0] = min(f[u][1] + f[v][0] + 1, f[u][0] + f[v][1] + 2);
    f[u][1] = min(f[u][1] + f[v][1] + 2, f[u][0] + dep);
  }
}
int main() {
  int N;
  cin >> N;
  for (int i = 2; i <= N; ++i) {
    int a;
    cin >> a;
    verts[a].push_back(i);
  }
  dfs(1, 0);
  cout << f[1][0] << endl;
  return 0;
}
