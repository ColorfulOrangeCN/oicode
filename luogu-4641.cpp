#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e5 + 1, lgn = 8, bitn = (1 << lgn) - 1;
int cnt[(1 << lgn)][lgn], presum[1 << (lgn * 2 + 1)];

int main() {
  int N, M;
  cin >> N >> M;
  for (int i = 0; i < N; ++i) {
    int a;
    cin >> a;
    ++presum[a];
    ++presum[a + (1 << 16)];
    for (int j = 0; j <= bitn; ++j) {
      const int num = (a + j) & bitn;
      for (int k = 0; k < lgn; ++k)
        if (num & (1 << k))
          ++cnt[j][k];
    }
  }
  partial_sum(presum, presum + (1 << (lgn * 2 + 1)), presum);
  int del = 0;
  long long ans = 0;
  for (int i = 1; i <= M; ++i) {
    char op;
    int x;
    cin >> op >> x;
    if (op == 'A') {
      del += x;
      del &= (1 << 16) - 1;
    } else {
      if (x < lgn) {
        ans += cnt[del & bitn][x];
      } else {
        for (int j = (1 << x); j <= (1 << 16) - 1; j += (1 << (x + 1)))
          ans += presum[j - del + (1 << x) - 1 + (1 << 16)] - presum[j - del - 1 + (1 << 16)];
      }
      // cout << ans << endl;
    }
  }
  cout << ans << endl;
  return 0;
}
