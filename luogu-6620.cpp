#include <bits/stdc++.h>
using namespace std;
#define int long long
constexpr int maxn = 1e3 + 1;
int N, X, P, M;
int A[maxn], B[maxn], dep[maxn];
int S[maxn][maxn];
inline int fpow(int x, int p) {
  int res = 1;
  while (p) {
    if (p & 1)
      (res *= x) %= P;
    (x *= x) %= P;
    p >>= 1;
  }
  return res;
}
signed main() {
  cin >> N >> X >> P >> M;
  S[0][0] = 1;
  for (int i = 1; i < maxn; ++i)
    for (int j = 1; j < maxn; ++j)
      S[i][j] = (j * S[i - 1][j] + S[i - 1][j - 1]) % P;
  dep[0] = 1;
  for (int i = 1; i <= M; ++i)
    dep[i] = (dep[i - 1] * (N - i + 1)) % P;
  copy_n(istream_iterator<int>(cin), M + 1, A);
  for (int i = 0; i <= M; ++i)
    for (int j = i; j <= M; ++j)
      (B[i] += S[j][i] * A[j]) %= P;
  int ans = 0;
  for (int i = 0; i <= M; ++i)
    (ans += B[i] * fpow(X, i) % P * fpow(X + 1, N - i) % P * dep[i] % P) %= P;
  cout << ans << endl;
  return 0;
}
