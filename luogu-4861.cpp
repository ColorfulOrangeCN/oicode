#include <bits/stdc++.h>
using namespace std;
typedef long long inte;
constexpr int maxn = (2 << 16);
inte org[maxn], sorg[maxn];
map<inte, inte> mp;
inline inte fpow(inte a, inte p, inte mods) {
  inte res = 1;
  while (p) {
    if (p & 1)
      (res *= a) %= mods;
    (a *= a) %= mods;
    p >>= 1;
  }
  return res;
}
int main() {
  inte g, P;
  cin >> P >> g;
  if (__gcd(P, g) != 1) {
    cout << "Let's go Blue Jays!" << endl;
    return 0;
  }
  org[0] = 1;
  for (int i = 1; i < maxn; ++i)
    org[i] = org[i - 1] * g % P;
  sorg[0] = 1;
  sorg[1] = org[maxn - 1] * g % P;
  assert(sorg[1] == fpow(g, maxn, P));
  for (int i = 1; i < maxn; ++i) {
    sorg[i] = sorg[i - 1] * sorg[1] % P;
    mp.insert(make_pair(sorg[i], i));
  }
  int n = 1;
  while (n--) {
    inte A = g;
    inte a = inte(maxn) * maxn + 1;
    for (int i = 1;i < maxn; ++i, (A *= g) %= P) {
      auto it = mp.find(A);
      if (it != mp.end()) {
        a = min(a, it->second * maxn - i);
      }
    }
    cout << a << endl;
  }
}
