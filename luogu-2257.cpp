#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e7 + 2;
bool isnp[maxn];
int primes[maxn / 10], pcnt = 0, mu[maxn], pmu[maxn];
inline void predo() {
  mu[1] = 1;
  for (int i = 2; i < maxn; ++i) {
    if (!isnp[i]) {
      primes[++pcnt] = i;
      mu[i] = -1;
    }
    for (int j = 1; j <= pcnt && i * primes[j] < maxn; ++j) {
      isnp[primes[j] * i] = true;
      if (i % primes[j] == 0) {
        mu[i * primes[j]] = 0;
        break;
      } else {
        mu[i * primes[j]] = -mu[i];
      }
    }
  }
  for (int i = 1; i < maxn; ++i)
    for (int j = 1; j <= pcnt && primes[j] * i < maxn; ++j)
      pmu[i * primes[j]] += mu[i];
  partial_sum(pmu + 1, pmu + maxn, pmu + 1);
}
typedef int inte;
int k;
inline inte calc(inte n, inte m) {
  int cur = 1;
  inte ans = 0;
  while (cur <= n && cur <= m) {
    const int nc = min(n / (n / cur), m / (m / cur)) + 1;
    ans += (n / (cur)) * (m / (cur)) * (pmu[nc - 1] - pmu[cur - 1]);
    cur = nc;
  }
  return ans;
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  predo();
  cin >> n;
  while (n--) {
    int b, d;
    cin >> b >> d;
    cout << calc(b, d) << '\n';
  }
}
