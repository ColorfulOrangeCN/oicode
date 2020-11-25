#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 2e5 + 1;
vector<int> verts[maxn];
typedef long long inte;
#define int long long
typedef pair<int, int> Meta;
int S[maxn], K[maxn], R[maxn];
int dis[maxn], dp[maxn];
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int N;
  cin >> N;
  priority_queue<Meta, vector<Meta>, greater<Meta> > q;
  for (int i = 1; i <= N; ++i) {
    cin >> S[i] >> K[i] >> R[i];
    q.push(Meta(K[i], i));
    for (int j = 0; j < R[i]; ++j) {
      int a;
      cin >> a;
      verts[a].push_back(i);
    }
    dp[i] = S[i];
  }
  while (!q.empty()) {
    static bool vis[maxn] = {};
    auto [d, u] = q.top();
    q.pop();
    if (vis[u])
      continue;
    // cerr << u << endl;
    vis[u] = true;
    dis[u] = d;
    for (int v : verts[u]) {
      if (vis[v] || dp[v] > K[v])
        continue;
      --R[v], dp[v] += d;
      if (!R[v])
        q.push(Meta(dp[v], v));
    }
  }
  cout << dis[1] << endl;
  return 0;
}
