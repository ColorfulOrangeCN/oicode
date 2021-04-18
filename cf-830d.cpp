#include <iostream>
using namespace std;
constexpr int maxn = 404;
typedef long long inte;
constexpr int mods = 1e9 + 7;
inte f[maxn][maxn];
inline inte fpow(inte x, int p) {
  inte res = 1;
  while (p) {
    if (p & 1)
      (res *= x) %= mods;
    (x *= x) %= mods;
    p >>= 1;
  }
  return res;
}
int main() {
  int K;
  cin >> K;
  f[K][1] = 1;
  for (int i = K - 1; i; --i) {
    for (int j = 1; j <= K - i + 1; ++j) {
      (f[i][j] = 2 * f[i + 1][j - 1] + 2 * f[i + 1][j] + 2 * f[i + 1][1] * f[i + 1][j - 1] % mods + (j == 1)) %= mods;
    }
  }
  inte ans = 0;
  for (int i = 1; i <= K; ++i)
    for (int j = 1; j <= K - i + 1; ++j)
      (ans += fpow(2, i - 1) * f[i][j] % mods) %= mods;
  cout << ans << endl;
  return 0;
}
