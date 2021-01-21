#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1 << 21;
constexpr double piv = 3.1415926535897;
typedef complex<double> Num;

Num F[maxn], G[maxn];
inline void brp(Num* f, int n) {
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
template<int type>
inline void DFT(Num *f, int len) {
  for (int n = 2; n <= len; n <<= 1) {
    const Num stp(cos(2 * piv / n), sin(2 * piv * type / n));
    for (int i = 0; i < len; i += n) {
      const int dn = n / 2;
      Num cur(1, 0);
      for (int j = 0; j < dn; ++j, cur *= stp) {
        const Num x = f[i + j], y = cur * f[i + j + dn];
        f[i + j] = x + y;
        f[i + j + dn] = x - y;
      }
    }
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  ++n, ++m;
  for (int i = 0; i < n; ++i) {
    double x;
    cin >> x;
    F[i].real(x);
  }
  for (int i = 0; i < m; ++i) {
    double x;
    cin >> x;
    G[i].real(x);
  }
  brp(F, maxn);
  DFT<1>(F, maxn);
  brp(G, maxn);
  DFT<1>(G, maxn);
  for (int i = 0; i < maxn; ++i)
    F[i] *= G[i];
  brp(F, maxn);
  DFT<-1>(F, maxn);
  for (int i = 0; i < n + m - 1; ++i)
    cout << int(F[i].real() / maxn + 0.5) << ' ';
  cout << '\n';
  return 0;
}
