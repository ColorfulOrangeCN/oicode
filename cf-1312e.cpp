#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 505;
int f[maxn][maxn], ans[maxn];
int A[maxn];
int main() {
  int N;
  cin >> N;
  for (int i = 1; i <= N; ++i)
    cin >> A[i], f[i][i] = A[i];
  for (int k = 1; k < N; ++k) {
    for (int i = 1; i + k <= N; ++i) {
      const int j = i + k;
      for (int s = i; s < j; ++s) {
        if (f[i][s] == f[s + 1][j] && f[i][s]) {
          f[i][j] = f[i][s] + 1;
          break;
        }
      }
    }
  }
  memset(ans, 0x3f, sizeof(ans));
  ans[0] = 0;
  for (int i = 1; i <= N; ++i)
    for (int s = 1; i - s >= 0; ++s)
      if (f[i - s + 1][i])
        ans[i] = min(ans[i], ans[i - s] + 1);
  // copy(ans + 1, ans + N + 1, ostream_iterator<int>(cout, " "));
  cout << ans[N] << endl;
  return 0;
}
