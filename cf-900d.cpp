#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long inte;
constexpr inte mods = 1e9 + 7;
inte f[2000];
inline inte modpow(inte a, int p) {
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
  int X, Y;
  cin >> X >> Y;
  if (Y % X) {
    cout << 0 << endl;
    return 0;
  }
  Y /= X;
  vector<inte> divs;
  for (int i = 1; i * i <= Y; ++i) {
    if (Y % i == 0) {
      divs.push_back(i);
      if (Y != i * i)
        divs.push_back(Y / i);
    }
  }
  sort(divs.begin(), divs.end(), greater<int>());
  for (int i = 0; i < divs.size(); ++i) {
    f[i] = modpow(2, Y / divs[i] - 1);
    for (int j = 0; j < divs.size(); ++j) {
      if (inte(Y) % (divs[i] * divs[j]) || divs[j] == 1)
        continue;
      const int t = lower_bound(divs.begin(), divs.end(), divs[i] * divs[j], greater<int>()) - divs.begin();
      (f[i] -= f[t]) %= mods;
    }
  }
  cout << (f[divs.size() - 1] + mods) % mods << endl;
  return 0;
}
