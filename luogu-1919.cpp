#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 1 << 21;
constexpr double piv = 3.1415926535897;
typedef complex<double> Num;
inline void brp(Num* f, int n) {
  static int rev[maxn];
  for (int i = 0; i < n; ++i) {
    rev[i] = rev[i >> 1] >> 1;
    if (i & 1)
      rev[i] |= n >> 1;
  }
  for (int i = 0; i < n; ++i)
    if (i < rev[i])
      swap(f[i], f[rev[i]]);
}
template<int type>
inline void dft(Num *f, int len) {
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
int sum[maxn + 1];
Num A[maxn], B[maxn];
int main() {
  string a, b;
  cin >> a >> b;
  reverse(a.begin(), a.end());
  reverse(b.begin(), b.end());
  for (int i = 0; i < a.length(); ++i)
    A[i].real(a[i] - '0');
  for (int i = 0; i < b.length(); ++i)
    B[i].real(b[i] - '0');
  brp(A, maxn);
  dft<1>(A, maxn);
  brp(B, maxn);
  dft<1>(B, maxn);
  for (int i = 0; i < maxn; ++i)
    A[i] *= B[i];
  brp(A, maxn);
  dft<-1>(A, maxn);
  // cerr << "FUCKED " << endl;
  int v = 0;
  for (int i = 0; i < maxn; ++i) {
    sum[i] = int(A[i].real() / maxn + 0.5) + v;
    v = sum[i] / 10;
    sum[i] %= 10;
    if (sum[i] < 0)
      sum[i] += 10, --v;
  }
  bool flag = false;
  for (int i = maxn - 1; i >= 0; --i) {
    flag |= sum[i];
    if (flag)
      cout << sum[i];
  }
  cout << '\n';
  return 0;
}
