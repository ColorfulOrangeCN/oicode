#include <bits/stdc++.h>
using namespace std;
typedef long long inte;
constexpr int maxn = 5e5 + 1;
constexpr inte mods = 1e9 + 7;
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
inline inte getop(inte x) {
  return fpow(x, mods - 2);
}
int main() {
  int N;
  cin >> N;
  inte P = 1, Q = 0;
  while (N--) {
    inte a, b;
    cin >> a >> b;
    (a *= getop(100)) %= mods;
    (b *= getop(100)) %= mods;
    const inte W = getop((1 - Q * b % mods + mods) % mods);
    Q = (b + a * a % mods * Q % mods * W) % mods;
    P = P * a % mods * W % mods;
  }
  cout << P << endl;
  return 0;
  
}
