#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e6 + 1, N = 1e6;
typedef long long inte;
constexpr inte mods = 1e9 + 7;
inte fact[maxn], invfact[maxn], inv[maxn], prenum[maxn];
inline inte getp(int v) {
  return fact[v] * prenum[v] % mods;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  inv[1] = 1;
  for (int i = 2; i <= N; ++i)
    inv[i] = (mods - mods / i) * inv[mods % i] % mods;
  fact[0] = invfact[0] = 1;
  for (int i = 1; i <= N; ++i) {
    fact[i] = fact[i - 1] * i % mods;
    invfact[i] = invfact[i - 1] * inv[i] % mods;
  }
  prenum[0] = 1;
  for (int i = 1; i <= N; ++i) {
    if (i & 1)
      prenum[i] = (prenum[i - 1] - invfact[i]) % mods;
    else
      prenum[i] = (prenum[i - 1] + invfact[i]) % mods;
  }
  int T;
  cin >> T;
  while (T--) {
    int n, m;
    cin >> n >> m;
    cout << (fact[n] * invfact[m] % mods * invfact[n - m] % mods * getp(n - m) % mods + mods) % mods << '\n';
  }
  return 0;
}
