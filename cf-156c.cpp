#include <iostream>
using namespace std;
typedef long long inte;
constexpr inte mods = 1e9 + 7;
constexpr int maxn = 2704;
inte modpow(inte a, int p = mods - 2) {
  inte res = 1;
  while (p) {
    if (p & 1)
      (res *= a) %= mods;
    (a *= a) %= mods;
    p >>= 1;
  }
  return res;
}
inte fac[maxn];
inline inte binom(int n, int m) {
  if (n < m)
    return 0;
  return fac[n] * modpow(fac[m]) % mods * modpow(fac[n - m]) % mods;
}
int main() {
  int T;
  cin >> T;
  fac[0] = 1;
  for (int i = 1; i < maxn; ++i)
    fac[i] = fac[i - 1] * i % mods;
  while (T--) {
    int s = 0;
    string str;
    cin >> str;
    for (char c : str)
      s += c - 'a' + 1;
    const int N = str.length();
    inte ans = 0;
    for (int i = 0; i <= N; ++i)
      (ans += (i & 1 ? -1 : 1) * binom(N, i) * binom(s - 26 * i - 1, N - 1)) %= mods;
    cout << (ans - 1 + mods) % mods << '\n';
  }
  return 0;
}
