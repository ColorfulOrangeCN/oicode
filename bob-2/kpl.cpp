#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 5e5 + 1;
vector<int> verts[maxn];

struct Node {
  int dep, maxdep, lson, topdep;
} nodes[maxn];
void predfs(int u, int la) {
  nodes[u].maxdep = nodes[u].dep = nodes[la].dep + 1;
  for (int v : verts[u]) {
    if (v == la)
      continue;
    predfs(v, u);
    nodes[u].maxdep = max(nodes[u].maxdep, nodes[v].maxdep);
    if (nodes[v].maxdep > nodes[nodes[u].lson].maxdep)
      nodes[u].lson = v;
  }
}
void initLC(int u, int la) {
  for (int v : verts[u]) {
    if (v == la)
      continue;
    if (v == nodes[u].lson)
      nodes[v].topdep = nodes[u].topdep + 1;
    else
      nodes[v].topdep = 1;
    initLC(v, u);
  }
}

int main() {
  ifstream fin("kpl.in");
  ofstream fout("kpl.out");
  #define cin fin
  #define cout fout
  int N;
  cin >> N;
  for (int i = 1; i < N; ++i) {
    int a, b;
    cin >> a >> b;
    verts[a].push_back(b);
    verts[b].push_back(a);
  }
  predfs(1, 0);
  nodes[1].topdep = 1;
  initLC(1, 0);
  static int ps[maxn];
  int tot = 0;
  for (int i = 1; i <= N; ++i) {
    if (verts[i].size() == 1)
      ps[tot++] = nodes[i].topdep;
  }
  sort(ps, ps + tot);
  long long ans = 0;
  for (int i = 0; i < tot; ++i)
    ans += (long long)ps[i] * (i + 1);
  cout << ans << endl;
  return 0;
}
