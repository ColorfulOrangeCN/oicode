#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e4 + 1;
int N, K, M;
struct Edge {
  int a, b, T, t;
} edges[maxn];
bool operator < (Edge a, Edge b) {
  return a.T < b.T;
}
int fa[maxn];
int getfa(int x) {
  if (fa[x] == x)
    return x;
  else
    return fa[x] = getfa(fa[x]);
}
int main() {
  cin >> N >> K >> M;
  for (int i = 1; i <= M; ++i)
    cin >> edges[i].a >> edges[i].b >> edges[i].T >> edges[i].t;
  sort(edges + 1, edges + M + 1);
  iota(fa + 1, fa + N + 1, 1);
  int ans = 0;
  for (int i = 1; i <= M; ++i) {
    if (getfa(edges[i].a) != getfa(edges[i].b)) {
      fa[getfa(edges[i].a)] = getfa(edges[i].b);
      if (K) {
        ans = max(ans, 0);
        --K;
      } else {
        ans = max(ans, edges[i].t);
      }
    }
  }
  return 0;
}
