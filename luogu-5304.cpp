#ifndef _FOL_UTILITY_
#define _FOL_UTILITY_

namespace fol {

  template <typename T>
  T exchange(T& l, const T& r) {
    T tmp = l;
    l = r;
    return tmp;
  }

  template <typename T>
  T& letmax(T& l, const T& r) {
    return l < r ? l = r : l;
  }

  template <typename T>
  T& letmin(T& l, const T& r) {
    return r < l ? l = r : l;
  }
  
}  // namespace fol
using fol::letmin;
#endif

#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e5 + 1;
#define int long long
typedef pair<int, int> Pair;
vector<Pair> verts[maxn];
int N, M, K;
int inter[maxn];
int ans;
void diji(int k, int t) {
  priority_queue<Pair, vector<Pair>, greater<Pair> > q;
  static bool vis[maxn], asked[maxn];
  memset(vis, 0, sizeof(vis));
  memset(asked, 0, sizeof(asked));
  for (int i = 0; i < K; ++i) {
    if (bool(inter[i] & (1 << k)) ^ t)
      q.push(make_pair(0, inter[i]));
    else
      asked[inter[i]] = true;
  }
  while (!q.empty()) {
    auto [d, u] = q.top();
    q.pop();
    if (vis[u])
      continue;
    vis[u] = true;
    if (asked[u]) {
      letmin(ans, d);
      break;
    }
    for (auto [v, dd] : verts[u]) {
      if (!vis[v])
        q.push(Pair(d + dd, v));
    }
  }
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    cin >> N >> M >> K;
    ans = ~0ull >> 2;
    fill(verts, verts + N + 1, vector<Pair>());
    for (int i = 0; i < M; ++i) {
      int x, y, z;
      cin >> x >> y >> z;
      verts[x].push_back(Pair(y, z));
    }
    copy_n(istream_iterator<int>(cin), K, inter);
    for (int i = 0; (1 << i) <= N; ++i)
      diji(i, 1), diji(i, 0);
    cout << ans << '\n';
  }
  return 0;
}
