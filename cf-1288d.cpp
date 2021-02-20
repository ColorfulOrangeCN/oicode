#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 3e5 + 5, maxb = 8, buf = (1 << maxb);
int A[maxn][maxb], f[maxn];
int vis[buf];
int N, M, X, Y;
inline int lowbit(int x) {return x & -x;}
inline bool check(int x) {
  memset(vis, 0, sizeof(vis));
  for (int i = 1; i <= N; ++i) {
    int v = 0;
    for (int j = 0; j < M; ++j)
      if (A[i][j] >= x)
        v |= (1 << j);
    vis[v] = i;
    f[i] = v;
   }
  // cerr << endl;
  for (int j = (1 << M) - 1; j; --j)
    if (vis[j])
      vis[j ^ lowbit(j)] = vis[j];
  for (int i = 1; i <= N; ++i) {
    const int t = vis[((1 << M) - 1) & (~f[i])];
    if (t) {
      X = t;
      Y = i;
      return true;
    }
  }
  return 0;
}
int main() {
  cin >> N >> M;
  for (int i = 1; i <= N; ++i)
    for (int j = 0; j < M; ++j)
      cin >> A[i][j];
  int L = 0, R = 1e9, ans = 0;
  while (L <= R) {
    const int mid = (L + R) / 2;
    if (check(mid)) {
      L = mid + 1;
      ans = mid;
    } else {
      R = mid - 1;
    }
  }
  check(ans);
  cout << X << ' ' << Y << endl;
  return 0;
}
