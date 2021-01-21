#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e6 + 1;
typedef long long inte;
inte ans[maxn];
inte fact[maxn], infa[maxn], inv[maxn];
int lg[maxn];
int main() {
  inte n, m;
  cin >> n >> m;
  inv[1] = 1;
  fact[0] = infa[0] = fact[1] = infa[1] = 1;
  lg[1] = 0;
  for (int i = 2; i <= n; ++i) {
    inv[i] = (m - m / i) * inv[m % i] % m;
    (fact[i] = fact[i - 1] * i) %= m;
    (infa[i] = infa[i - 1] * inv[i]) %= m;
    lg[i] = lg[i / 2] + 1;
  }
  ans[1] = ans[2] = 1;
  ans[3] = 2;
  int l = 1, r = 1;
  for (int i = 4; i <= n; ++i) {
    if (i - (1 << lg[i]) + 1 <= (1 << lg[i] - 1))
      l++;
    else
      r++;
    ans[i] = ans[l] * ans[r] % m * fact[i - 1] % m * infa[i - l - 1] % m * infa[l] % m;
  }
  cout << ans[n] << endl;
  return 0;
}
