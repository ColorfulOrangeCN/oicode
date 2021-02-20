#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 4e5 + 4;
typedef long long inte;
#define int long long
inline void butterfly(inte* f, int n) {
  static int rev[maxn];
    for (int i = 0; i < n; ++i) {
      rev[i] = rev[i >> 1] >> 1;
      if (i & 1)
        rev[i] |= (n >> 1);
    }
  for (int i = 0; i < n; ++i)
    if (i < rev[i])
      swap(f[i], f[rev[i]]);
}
constexpr int mods = 5 * (1 << 25) + 1, _g = 3;
inline inte fpow(inte a, int p) {
  inte res = 1;
  while (p) {
    if (p & 1)
      (res *= a) %= mods;
    (a *= a) %= mods;
    p >>= 1;
  }
  return res;
}
void ntt(inte *f, int l, inte g) {
  butterfly(f, l);
  for (int n = 2; n <= l; n <<= 1) {
    const inte stp = fpow(g, (mods - 1) / n);
    for (int i = 0; i < l; i += n) {
      const int dn = n / 2;
      inte cur = 1;
      for (int j = 0; j < dn; ++j, (cur *= stp) %= mods) {
        const inte x = f[i + j], y = cur * f[i + j + dn] % mods;
        f[i + j] = (x + y) % mods;
        f[i + j + dn] = (x - y) % mods;
      }
    }
  }
}
inte A[maxn], B[maxn];
inte invf[maxn];
signed main() {
  int N;
  cin >> N;
  const int rn = (1 << (int)ceil(log2(2 * N + 2)));
  invf[0] = 1;
  for (int i = 1; i <= N; ++i)
    invf[i] = invf[i - 1] * fpow(i, mods - 2) % mods;
  A[0] = 1;
  for (int i = 1; i <= N; ++i) {
    A[i] = (i & 1 ? -1 : 1) * invf[i];
    B[i] = fpow(i, N) * invf[i] % mods;
  }
  ntt(A, rn, _g);
  ntt(B, rn, _g);
  for (int i = 0; i < rn; ++i)
    (A[i] *= B[i]) %= mods;
  ntt(A, rn, fpow(_g, mods - 2));
  for (int i = 0, inv = fpow(rn, mods - 2); i <= N; ++i) {
    (A[i] *= inv) %= mods;
    cout << (A[i] + mods) % mods << ' ';
  }
  return 0;
}
