#include <bits/stdc++.h>
using namespace std;
typedef long long inte;
inte extgcd(inte a, inte b, inte& x, inte& y) {
  if (b == 0) {
    x = 1, y = 0;
    return a;
  }
  const inte t = extgcd(b, a % b, y, x);
  y -= a / b * x;
  return t;
}
inline inte getop(inte x, inte p) {
  inte a, b;
  extgcd(x, p, a, b);
  return (a % p + p) % p;
}
constexpr int maxn = 10;
inte A[maxn], B[maxn];
int K;
inline inte getcrt() {
  inte lcm = 1;
  for (int i = 0; i < K; ++i)
    lcm *= B[i];
  inte ans = 0;
  // cerr << lcm << endl;
  for (int i = 0; i < K; ++i) {
    __int128 t = A[i] % B[i];
    // cerr << A[i] << ' ' << getop(lcm / B[i], B[i]) << endl;
    (t *= getop(lcm / B[i], B[i])) %= lcm;
    (t *= lcm / B[i]) %= lcm;
    (ans += t) %= lcm;
  }
  return (ans + lcm) % lcm;
}
int main() {
  cin >> K;
  copy_n(istream_iterator<int>(cin), K, A);
  copy_n(istream_iterator<int>(cin), K, B);
  cout << getcrt() << endl;
  return 0;
}
