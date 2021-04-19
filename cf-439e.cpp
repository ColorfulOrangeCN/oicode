#include <iostream>
using namespace std;
constexpr int maxn = 1e5 + 4;
typedef long long inte;
constexpr inte mods = 1e9 + 7;
int prm[maxn], pc = 0;
int vis[maxn], mu[maxn];
inte fac[maxn];
inline inte modpow(inte a, int p = mods - 2) {
  inte res = 1;
  while (p) {
    if (p & 1)
      (res *= a) %= mods;
    (a *= a) %= mods;
    p >>= 1;
  }
  return res;
}
inline inte binom(int n, int m) {
  if (n < m)
    return 0;
  return fac[n] * modpow(fac[m]) % mods * modpow(fac[n - m]) % mods;
}
int N, M;
inline inte f(int d) {
  return binom(d - 1, M - 1);
}
int main() {
  mu[1] = 1;
  fac[0] = 1;
  for (int i = 1; i < maxn; ++i)
    fac[i] = fac[i - 1] * i % mods;
  for (int i = 2; i < maxn; ++i) {
    if (!vis[i]) {
      prm[++pc] = i;
      mu[i] = -1;
    }
    for (int j = 1; j <= pc && i * prm[j] < maxn; ++j) {
      vis[i * prm[j]] = j;
      if (i % prm[j] == 0) {
        mu[i * prm[j]] = 0;
        break;
      }
      mu[i * prm[j]] = -mu[i];
    }
  }
  int Q;
  cin >> Q;
  while (Q--) {
    cin >> N >> M;
    inte ans = 0;
    for (int i = 1; i * i <= N; ++i) {
      if (N % i == 0) {
        (ans += mu[N / i] * f(i)) %= mods;
        if (N != i * i)
          (ans += mu[i] * f(N / i)) %= mods;
      }
    }
    cout << (ans + mods) % mods << endl;
  }
  return 0;
}
