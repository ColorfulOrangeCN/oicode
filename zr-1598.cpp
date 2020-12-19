#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 5000, mods = 1e9 + 7;
int A[maxn], before[maxn];
typedef long long inte;
inte f[maxn][maxn];
int main() {
  int N;
  cin >> N;
  copy_n(istream_iterator<int>(cin), N, A);
  for (int i = 0; i < N; ++i) {
    if (A[i] == i)
      before[i] |= 3;
    for (int j = i + 1; j < A[i]; ++j)
      before[j] |= 1;
    for (int j = i - 1; j > A[i]; --j)
      before[j] |= 2;
  }
  for (int i = 0; i < N; ++i) {
    if (before[i] == 3) {
      cerr << "GAP" << endl;
      cout << "0\n";
      return 0;
    }
  }
  f[0][0] = 1;
  for (int i = 1; i < N - 1; ++i) {
    if (before[i] == 2) {
      for (int j = i - 1; j >= 0; --j)
        f[i][j] = (f[i - 1][j] + f[i][j + 1]) % mods;
    } else {
      for (int j = 1; j <= i; ++j)
        f[i][j] = (f[i - 1][j - 1] + f[i][j - 1]) % mods;
    }
  }
  inte ans = 0;
  for (int i = 0; i < N - 1; ++i)
    (ans += f[N - 2][i]) %= mods;
  cout << ans << endl;
  return 0;
}
