#ifndef _FOL_UTILITY_
#define _FOL_UTILITY_

namespace fol {

  template <typename T>
  T exchange(T& l, const T& r) {
    T tmp = l;
    l = r;
    return tmp;
  }

  template <typename T>
  T& letmax(T& l, const T& r) {
    return l < r ? l = r : l;
  }

  template <typename T>
  T& letmin(T& l, const T& r) {
    return r < l ? l = r : l;
  }
  
}  // namespace fol

#endif

#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 51;
char str[maxn];
int f[maxn][maxn];
using fol::letmin;
int main() {
  cin >> str;
  const int N = strlen(str);
  memset(f, 0x3f, sizeof(f));
  f[0][0] = 1;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j <= i; ++j) {
      letmin(f[i + 1][j], f[i][j] + 1);
      letmin(f[i][i], f[i][j] + 1);
      if (i + (i - j + 1) >= N)
        continue;
      bool gg = true;
      for (int k = 0; j + k <= i; ++k)
        gg &= (str[j + k] == str[i + k + 1]);
      if (gg)
        letmin(f[i + (i - j + 1)][j], f[i][j] + 1);
    }
  }
  int ans = ~0u>>2;
  for (int k = 0; k < N; ++k)
    letmin(ans, f[N - 1][k]);
  cout << ans << endl;
  return 0;
}
