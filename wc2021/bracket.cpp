#define NDEBUG
#include <bits/stdc++.h>
using namespace std;
const static int maxn = 3e5 + 4;
int par[maxn];
int getPar(int x) {
  if (par[x] == x)
    return x;
  else
    return par[x] = getPar(par[x]);
}
typedef pair<int, int> Edge;
list<Edge> verts[maxn];
int sz[maxn];

int main() {
  ifstream fin("bracket.in");
  ofstream fout("bracket.out");
#define cin fin
#define cout fout
  int N, M, K;
  cin >> N >> M >> K;
  for (int i = 0; i < M; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    verts[v].push_back(Edge(w, u));
  }
  for (int i = 1; i <= N; ++i) {
    par[i] = i;
    verts[i].sort();
  }
  stack<int> q;

  bool flag;
  do {
    flag = false;
    for (int i = 1; i <= N; ++i)
      q.push(i);
    while (!q.empty()) {
      const int u = q.top();
      q.pop();
      if (par[u] != u)
        continue;
      Edge la = Edge(0, 0);
      int cnt = verts[u].size();
      for (list<Edge>::iterator it = verts[u].begin(); cnt; --cnt) {
        if (la.first == it->first && getPar(la.second) != getPar(it->second)) {
          verts[getPar(it->second)].merge(verts[getPar(la.second)]);
          verts[getPar(la.second)].clear();
          par[getPar(la.second)] = par[getPar(it->second)];
          q.push(it->second);
          flag = true;
        }
        la = *it;
        ++it;
      }
    }
  } while (flag);
  
  long long ans = 0;
  for (int i = 1; i <= N; ++i)
    ++sz[getPar(i)];
  for (int i = 1; i <= N; ++i)
    ans += ((long long)sz[i]) * (sz[i] - 1) / 2;
  cout << ans << endl;
  return 0;
}
