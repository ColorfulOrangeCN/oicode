#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e5 + 1, inf = 0x3f3f3f3f;
int col[maxn], f[maxn][101];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int N, K;
    cin >> N >> K;
    for (int i = 1; i <= N; ++i)
      cin >> col[i];
    for (int i = 1; i <= N; ++i) {
      f[i][col[i]] = f[i - 1][col[i]];
      for (int j = 1; j <= 100; ++j)
        if (j != col[i])
          f[i][j] = inf;
      for (int j = 1; j <= 100; ++j)
        f[i][j] = min(f[i][j], f[max(i - K, 0)][j] + 1);
    }
    int ans = inf;
    for (int j = 1; j <= 100; ++j) {
      ans = min(ans, f[N][j]);
    }
    cout << ans << endl;
  }
  return 0;
}
