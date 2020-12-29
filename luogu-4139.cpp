#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e7 + 1;
int phi[maxn];
bool isnp[maxn];
int primes[maxn], cnt = 0;
void init() {
  isnp[1] = true;
  for (int i = 2; i < maxn; ++i) {
    if (phi[i] == 0) {
      primes[++cnt] = i;
      phi[i] = i - 1;
    }
    for (int j = 1; i * primes[j] < maxn && j <= cnt; ++j) {
      if (i % primes[j] == 0) {
        phi[i * primes[j]] = phi[i] * primes[j];
        break;
      } else {
        phi[i * primes[j]] = phi[i] * (primes[j] - 1);
      }
    }
  }
}
typedef long long inte;
inline inte bipow(inte x, int p, inte mods) {
  inte res = 1;
  while (p) {
    if (p & 1)
      (res *= x) %= mods;
    (x *= x) %= mods;
    p >>= 1;
  }
  return res;
}
inte eular(inte p) {
  if (p <= 2)
    return 0;
  return bipow(2, phi[p] + eular(phi[p]), p);
}
int main() {
  init();
  int T;
  cin >> T;
  while (T--) {
    int p;
    cin >> p;
    cout << eular(p) << '\n';
  }
  return 0;
}
