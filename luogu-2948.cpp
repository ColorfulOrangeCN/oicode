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
using namespace fol;
#endif

#include <bits/stdc++.h>
using namespace std;
constexpr int maxt = 1e4 + 1, maxp = 101;
int f[maxt][maxp];
typedef tuple<int, int, int> Lesson;
Lesson ls[maxp];
int mintime[maxp];
int main() {
  int L = 0, T, S, N;
  cin >> T >> S >> N;
  for (int i = 0; i < S; ++i)
    cin >> get<0>(ls[i]) >> get<1>(ls[i]) >> get<2>(ls[i]);
  memset(mintime, 0x3f, sizeof(mintime));
  for (int i = 0; i < N; ++i) {
    int c, t;
    cin >> c >> t;
    letmin(mintime[c], t);
  }
  for (int j = 1; j < maxp; ++j)
    letmin(mintime[j], mintime[j - 1]);
  sort(ls, ls + S);
  memset(f, -0x3f, sizeof(f));
  f[0][1] = 0;
  for (int i = 0; i < T; ++i) {
    while (get<0>(ls[L]) == i) {
      auto [_, l, p] = ls[L];
      ++L;
      if (i + l > T)
        continue;
      for (int j = 1; j < maxp; ++j)
        letmax(f[i + l][p], f[i][j]);
    }
    for (int j = 1; j < maxp; ++j) {
      letmax(f[i + 1][j], f[i][j]);
      // cerr << i << ' ' << j << ' ' << f[i][j] << endl;
      if (i + mintime[j] <= T)
        letmax(f[i + mintime[j]][j], f[i][j] + 1);
    }
  }
  int ans = 0;
  for (int j = 1; j < maxp; ++j)
    letmax(ans, f[T][j]);
  cout << ans << endl;
  return 0;
}
