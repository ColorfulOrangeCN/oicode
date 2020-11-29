#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e5 + 1;
char str[maxn];
int cnt[maxn];
int main() {
  int T;
  cin >> T;
  while (T--) {
    int N, P, K, x, y;
    cin >> N >> P >> K >> (str + 1) >> x >> y;
    int L = 1, R = 1;
    int ans = 0x7fffffff;
    for (int i = P; i <= N; ++i)
      if (str[i] == '1')
        ++cnt[i % K];
    int m = P % K;
    for (int i = P; i <= N; ++i) {
      // cerr << cnt[m] << endl;
      ans = min(ans, ((N - i) / K + 1 - cnt[m]) * x + (i - P) * y);
      if (str[i] == '1')
        --cnt[i % K];
      m = (m + 1) % K;
    }
    cout << ans << '\n';
  }
  return 0;
}
