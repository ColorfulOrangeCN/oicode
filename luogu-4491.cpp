#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 4e5 + 4, maxv = 1e7 + 4;
typedef long long inte;
constexpr inte mods = 1004535809, _g = 3;
inline inte fpow(inte a, inte p) {
  inte res = 1;
  while (p) {
    if (p & 1)
      (res *= a) %= mods;
    (a *= a) %= mods;
    p >>= 1;
  }
  return res;
}
inline inte getinv(inte a) {return fpow(a, mods - 2);}
int rev[maxn];
inline void brp(int n) {
  for (int i = 1; i < n; ++i) {
    rev[i] = rev[i >> 1] >> 1;
    if (i & 1)
      rev[i] |= n >> 1;
  }
}
inline void ntt(inte* f, int l, int id) {
  const inte g = id ? getinv(_g) : _g;
  for (int i = 0; i < l; ++i)
    if (i < rev[i])
      swap(f[i], f[rev[i]]);
  for (int n = 2; n <= l; n <<= 1) {
    const inte stp = fpow(g, (mods - 1) / n);
    const int dn = n / 2;
    for (int i = 0; i < l; i += n) {
      inte cur = 1;
      for (int j = 0; j < dn; ++j, (cur *= stp) %= mods) {
        const inte x = f[i + j], y = f[i + j + dn] * cur % mods;
        f[i + j] = (x + y) % mods;
        f[i + j + dn] = (x - y) % mods;
      }
    }
  }
  if (id) {
    const inte invl = getinv(l);
    for (int i = 0; i < l; ++i)
      (f[i] *= invl) %= mods;
  }
}
inte A[maxn], B[maxn];
inte fac[maxv], invf[maxv];
inline inte bio(int m, int k) {
  return fac[m] * invf[k] % mods * invf[m - k] % mods;
}
int main() {
  int N, M, S;
  cin >> N >> M >> S;
  fac[0] = 1;
  for (int i = 1; i <= max(N, M); ++i)
    fac[i] = fac[i - 1] * i % mods;
  invf[max(N, M)] = getinv(fac[max(N, M)]);
  for (int i = max(N, M) - 1; i >= 0; --i)
    invf[i] = invf[i + 1] * (i + 1) % mods, assert(invf[i] * fac[i] % mods == 1);
  for (int i = 0; i <= M; ++i) {
    if (N >= S * i)
      A[i] = fac[i] * bio(M, i) % mods * fac[N] % mods * fpow(invf[S], i) % mods * invf[N - S * i] % mods * fpow(M - i, N - S * i) % mods;
    B[i] = (i & 1 ? -invf[i] : invf[i]);
  }
  // copy(A, A + M + 1, ostream_iterator<inte>(cerr, " "));
  // cerr << endl;
  reverse(A, A + M + 1);
  const int lim = (1 << (int)ceil(log2(2 * M + 2)));
  brp(lim);
  ntt(A, lim, 0);
  ntt(B, lim, 0);
  for (int i = 0; i < lim; ++i)
    (A[i] *= B[i]) %= mods;
  ntt(A, lim, 1);
  reverse(A, A + M + 1);
  inte ans = 0;
  for (int i = 0; i <= M; ++i) {
    inte w;
    cin >> w;
    // cerr << A[i] << endl;
    (ans += w * A[i] % mods * invf[i] % mods) %= mods;
  }
  cout << (ans + mods) % mods << endl;
  return 0;
}
