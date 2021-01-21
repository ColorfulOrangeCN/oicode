#include <bits/stdc++.h>
using namespace std;
int N, M;
typedef long long inte;
constexpr int maxn = 7504;
inte comb[maxn][maxn], fact[maxn];
inline inte calc(int s) {
  static inte dp[maxn];
  const int lm = N / s;
  dp[0] = -1;
  for (int i = 1; i <= lm; ++i) {
    for (int j = 1; j <= i; ++j) {
      (dp[i] += dp[i - j] * comb[i * s - 1][j * s - 1] % (M - 1) * fact[j * s - 1] % (M - 1)) %= (M - 1);
    }
    dp[i] = -dp[i];
  }
  inte res = 0;
  for (int i = 1; i <= lm; ++i)
    (res += dp[i] * comb[N][i * s] % (M - 1) * fact[N - i * s] % (M - 1)) %= (M - 1);
  return res;
}
inline inte fpow(inte a, inte p) {
  inte res = 1;
  while (p) {
    if (p & 1)
      (res *= a) %= M;
    (a *= a) %= M;
    p >>= 1;
  }
  return res;
}
bool vis[maxn] = {0};
int main() {
  cin >> N >> M;
  comb[0][0] = 1;
  for (int n = 1; n < maxn; ++n) {
    comb[n][0] = 1;
    for (int k = 1; k <= n; ++k)
      comb[n][k] = (comb[n - 1][k] + comb[n - 1][k - 1]) % (M - 1);
  }
  fact[0] = 1;
  for (int i = 1; i < maxn; ++i)
    fact[i] = fact[i - 1] * i % (M - 1);
  inte ans = 1;
  for (int i = 2; i <= N; ++i) {
    if (vis[i])
      continue;
    for (int j = 2; i * j <= N; ++j) {
      vis[i * j] = true;
    }
    int x = 1;
    while (N / i >= x) {
      x *= i;
      (ans *= fpow(i, (calc(x) + M - 1) % (M - 1))) %= M;
    }
  }
  cout << ans << endl;
  return 0;
}
