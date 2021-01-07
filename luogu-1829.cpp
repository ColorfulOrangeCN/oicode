#include <bits/stdc++.h>
using namespace std;

#define int long long

constexpr int maxn = 1e7 + 2;
bool isnp[maxn];
int pm[maxn], pcnt = 0, mu[maxn];
typedef long long inte;
constexpr int mods = 20101009;
inte sf[maxn];
inline void init() {
  mu[1] = 1;
  for (int i = 2; i < maxn; ++i) {
    if (!isnp[i]) {
      pm[++pcnt] = i;
      mu[i] = -1;
    }
    for (int j = 1; j <= pcnt && i * pm[j] < maxn; ++j) {
      isnp[i * pm[j]] = true;
      if (i % pm[j] == 0) {
        mu[i * pm[j]] = 0;
        break;
      }
      mu[i * pm[j]] = -mu[i];
    }
  }
  for (inte i = 1; i < maxn; ++i)
    (sf[i] = sf[i - 1] + i * i * mu[i] % mods) %= mods;
}
inline inte g(inte n, inte m) {
  return (n * (n + 1) / 2) % mods * (m * (m + 1) / 2 % mods) % mods;
}
inline inte solve(inte n, inte m) {
  if (n > m)
    swap(n, m);
  inte ans = 0;
  for (int l = 1, r; l <= n; l = r + 1) {
    r = min(n / (n / l), m / (m / l));
    (ans += (sf[r] - sf[l - 1]) % mods * g(n / l, m / l) % mods) %= mods;
  }
  return ans;
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  init();
  inte n, m;
  cin >> n >> m;
  if (n > m)
    swap(n, m);
  inte ans = 0;
  for (int l = 1, r; l <= n; l = r + 1) {
    r = min(n / (n / l), m / (m / l));
    (ans += inte(l + r) * (r - l + 1) / 2 % mods * solve(n / l, m / l) % mods) %= mods;
  }
  cout << (ans + mods) % mods << '\n';
}
