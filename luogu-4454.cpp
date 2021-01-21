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
  cin >> g >> P;
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
  int n;
  cin >> n;
  while (n--) {
    inte A, B;
    cin >> A >> B;
    inte a = -1;
    for (int i = 0;; ++i, (A *= g) %= P) {
      auto it = mp.find(A);
      if (it != mp.end()) {
        // cerr << "FAKE" << endl;
        // cerr << it->second << ' ' << i << ' ' << A << endl;
        a = it->second * maxn - i;
        break;
      }
    }
    cout << fpow(B, a, P) << endl;
  }
}
