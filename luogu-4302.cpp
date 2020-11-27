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
constexpr int maxn = 101;
int f[maxn][maxn];
char str[maxn];
inline int calc(int x) {
  int c = 0;
  do {
    ++c;
    x /= 10;
  } while(x);
  return c;
}
using fol::letmin;
int main() {
  cin >> (str + 1);
  int N = strlen(str + 1);
  for (int i = 1; i <= N; ++i)
    f[i][i] = 1;
  for (int k = 1; k < N; ++k) {
    for (int i = 1; i <= N - k; ++i) {
      const int j = i + k;
      f[i][j] = j - i + 1;
      for (int c = i + 1; c <= j; ++c)
        letmin(f[i][j], f[i][c - 1] + f[c][j]);
      for (int c = 1; i + c <= j; ++c) {
        if ((k + 1) % c)
          continue;
        bool gg = true;
        for (int s = i + c; s <= j; ++s)
          gg &= (str[s] == str[s - c]);
        if (gg)
          letmin(f[i][j], calc((k + 1) / c) + 2 + f[i][i + c - 1]);
      }
    }
  }
  cout << f[1][N] << endl;
  return 0;
}
