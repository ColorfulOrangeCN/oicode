#include <bits/stdc++.h>
using namespace std;
typedef long long inte;
#define int long long
constexpr int mods = 19940417;
constexpr inte inv2 = 9970209, inv6 = 3323403;
inline inte sum1(inte l, inte r) {
  return (l + r) * (r - l + 1) % mods * inv2 % mods;
}
inline inte presum2(inte k) {
  return k * (k + 1) % mods * (2 * k + 1) % mods * inv6 % mods;
}
inline inte calc(inte n) {
  inte res = n * n % mods;
  for (int l = 1, r; l <= n; l = r + 1) {
    r = n / (n / l);
    assert(n / l == n / r);
    (res -= sum1(l, r) * (n / l) % mods) %= mods;
  }
  // cerr << res << endl;
  return res;
}
inline inte ca(inte n, inte m) {
  inte res = n * n % mods * m % mods;
  for (int l = 1, r; l <= n; l = r + 1) {
    r = min(n / (n / l), m / (m / l));
    (res -= sum1(l, r) * (m * (n / l) % mods + n * (m / l) % mods) % mods) %= mods;
    (res += (presum2(r) - presum2(l - 1)) % mods * (n / l) % mods * (m / l) % mods) %= mods;
  }
  return res;
}
signed main() {
  int N, M;
  cin >> N >> M;
  if (N > M)
    swap(N, M);
  cout << ((calc(N) * calc(M) - ca(N, M)) % mods + mods) % mods << endl;
  return 0;
}
