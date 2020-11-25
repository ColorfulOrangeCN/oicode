#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 101;
int presum[maxn][maxn];
bitset<maxn * maxn * 5> f, t;
int main() {
  freopen("divide.in", "r", stdin);
  freopen("divide.out", "w", stdout);
  int N = 100, M = 100;
  cin >> N >> M;
  int tot = 0;
  for (int i = 1; i <= N; ++i)
    for (int j = 1; j <= M; ++j)
      cin >> presum[i][j], tot += presum[i][j], presum[i][j] += presum[i][j - 1];
  f[0] = true;
  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j <= M; ++j)
      t |= (f << presum[i][j]);
    f = t;
  }
  int ans = 0x3f3f3f3f;
  for (int i = 0; i < maxn * maxn * 5; ++i)
    if (f[i])
      ans = min(ans, abs(tot - i * 2));
  cout << ans << endl;
  return 0;
}
