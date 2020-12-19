#include <bits/stdc++.h>
using namespace std;
constexpr int maxm = 105, maxp = 1e7 + 5, mods = 998244353;
typedef long long inte;
#define int long long
inte comb[maxm][maxm];
inte N, M;
int cnt[maxm];
int la[maxp];
inte a[maxp];
void bagMul(const int a[], const int b[], int res[]) {
  for (int i = M; i >= 0; --i) {
    inte t = 0;
    for (int j = 0; j <= i; ++j)
      (t += a[j] * b[i - j] % mods * comb[i][j]) %= mods;
    res[i] = t;
  }
}
void bagPow(int x, inte p, int res[]) {
  static int cc[maxm];
  for (int i = 0; i <= M; ++i) {
    cc[i] = (i <= x);
    res[i] = 0;
  }
  res[0] = 1;
  while (p) {
    if (p & 1)
      bagMul(res, cc, res);
    bagMul(cc, cc, cc);
    p >>= 1;
  }
}
signed main() {
  cin >> N >> M;
  inte A, B, P;
  cin >> a[1] >> A >> B >> P;
  for (inte i = 1; i <= N; ++i) {
    if (la[a[i]]) {
      const inte len = i - la[a[i]];
      const inte times = (N - i + 1) / len;
      for (inte j = la[a[i]]; j < i; ++j)
        cnt[min(a[j], M)] += times;
      for (int j = la[a[i]]; j + (times + 1) * len <= N; ++j)
        ++cnt[min(a[j], M)];
      break;
    }
    ++cnt[min(a[i], M)];
    la[a[i]] = i;
    a[i + 1] = (A * a[i] + B) % P + 1;
  }
  comb[0][0] = 1;
  for (int i = 1; i <= M; ++i)
    for (int j = 0; j <= i; ++j)
      comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % mods;
  static int ans[maxm] = {1};
  for (int i = 0; i <= M; ++i) {
    static int tmp[maxm];
    bagPow(i, cnt[i], tmp);
    bagMul(tmp, ans, ans);
  }
  cout << ans[M] << endl;
  return 0;
}
