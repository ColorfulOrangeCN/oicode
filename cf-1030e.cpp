#include <bits/stdc++.h>
using namespace std;
#define int long long
constexpr int maxn = 3e5 + 4;
int C[maxn], pre[maxn][2];
signed main() {
  int N;
  cin >> N;
  for (int i = 1; i <= N; ++i) {
    int a;
    cin >> a;
    C[i] = __builtin_popcountll(a);
  }
  // for (int i = 1; i <= N; ++i)
    // cout << C[i] << ' ';
  // cout << endl;
  int pp = 0;
  for (int i = 1; i <= N; ++i) {
    pp ^= C[i] & 1;
    pre[i][0] = pre[i - 1][0];
    pre[i][1] = pre[i - 1][1];
    ++pre[i][pp];
  }
  int ans = 0, psum = 0;
  for (int i = 1; i <= N; ++i) {
    int sum = 0, maxv = 0;
    for (int j = i; j <= N && j <= i + 64; ++j) {
      sum += C[j];
      maxv = max(maxv, C[j]);
      if ((sum & 1) == 0 && maxv * 2 <= sum)
        ++ans;
    }
    // cerr << "FUCK" << i << endl;
    // cerr << t << endl;
    // cerr << pre[min(N, i + 64)][psum] - pre[i - 1][psum] << endl;
    // assert(pre[min(N, i + 64)][psum] - pre[i - 1][psum] == t);
    ans += pre[N][psum] - pre[min(N, i + 64)][psum];
    psum ^= C[i] & 1;
  }
  cout << ans << endl;
  return 0;
}
