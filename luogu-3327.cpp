#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 5e4 + 2;
bool isnp[maxn];
int pm[maxn], pcnt = 0, mu[maxn];
typedef long long inte;
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
  for (int i = 1; i < maxn; ++i) {
    for (int l = 1, r; l <= i; l = r + 1) {
      r = i / (i / l);
      sf[i] += inte(i / l) * (r - l + 1);
      // cerr << i << ' ' << sf[i] << endl;
    }
  }
  // copy_n(mu + 1, 10, ostream_iterator<int>(cerr, "\n"));
  partial_sum(mu + 1, mu + maxn, mu + 1);
}
inline inte solve(int n, int m) {
  if (n > m)
    swap(n, m);
  inte ans = 0;
  for (int l = 1, r; l <= n; l = r + 1) {
    r = min(n / (n / l), m / (m / l));
    ans += (mu[r] - mu[l - 1]) * sf[n / l] * sf[m / l];
  }
  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  init();
  while (T--) {
    int n, m;
    cin >> n >> m;
    cout << solve(n, m) << '\n';
  }
}
