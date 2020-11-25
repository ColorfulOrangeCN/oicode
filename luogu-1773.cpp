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
constexpr int maxn = 1e3 + 1, maxm = 50;
char str[maxn];
int num[maxn][maxn];
int f[maxn][maxm];

int main() {
  int m;
  cin >> (str + 1) >> m;
  const int N = strlen(str + 1);
  for (int i = 1; i <= N; ++i)
    for (int j = i; j <= N; ++j)
      num[i][j] = (num[i][j - 1] * 10 + str[j] - '0') % m;
  memset(f, 0x3f, sizeof(f));
  for (int i = 1; i <= N; ++i)
    f[i][num[1][i]] = 0;
  for (int i = 2; i <= N; ++i)
    for (int j = 0; j < m; ++j)
      for (int k = 1; k < i; ++k)
        fol::letmin(f[i][j * num[k + 1][i] % m], f[k][j] + 1);
  for (int j = 0; j < m; ++j) {
    if (f[N][j] <= N) {
      cout << j << ' ' << f[N][j] << ' ';
      break;
    }
  }
  for (int j = m - 1; j >= 0; --j) {
    if (f[N][j] <= N) {
      cout << j << ' ' << f[N][j] << ' ';
      break;
    }
  }
  return 0;
}
