#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e6 + 5;
typedef long long inte;
int A[maxn];
inte C[maxn];
typedef pair<inte, int> Meta;
Meta fd[maxn];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int N, M;
  cin >> N >> M;
  copy_n(istream_iterator<int>(cin), N, A + 1);
  for (int i = 0; i < M; ++i) {
    int k;
    cin >> k;
    for (int i = 1; i <= N; ++i)
      C[i] = C[i - 1] + A[i] - k;
    int fc = 0;
    for (int i = 1; i <= N; ++i) {
      if (fd[fc].first > C[i])
        fd[++fc] = Meta(C[i], i);
    }
    k = fc; // Meaning Change
    inte la = -(~0ull>>2);
    int ans = 0;
    for (int i = N; i >= 1; --i) {
      // cerr << i << ' ' << C[i] << ' ' << la << endl;
      if (C[i] <= la)
        continue;
      while (k && fd[k - 1].first <= C[i])
        --k;
      // cerr << i << ' ' << k << ' ' << fd[k].first << endl;
      if (fd[k].first <= C[i])
        ans = max(ans, i - fd[k].second);
      la = C[i];
    }
    cout << ans << ' ';
  }
  return 0;
}
