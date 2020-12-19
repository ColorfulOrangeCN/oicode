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
constexpr int maxn = 101, lgn = 31, maxw = 1001;
int N, W;
typedef long long inte;
inte f[maxw][lgn], g[maxw][lgn];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  while (true) {
    cin >> N >> W;
    if (N == -1 && W == -1)
      break;
    memset(f, 0, sizeof(f));
    memset(g, 0, sizeof(g));
    for (int i = 0; i < N; ++i) {
      int w, v;
      cin >> w >> v;
      int t = 0;
      while (!(w & 1)) {
        ++t;
        w >>= 1;
      }
      for (int i = maxw - 1; i >= w; --i)
        letmax(f[i][t], f[i - w][t] + v);
    }
    for (int j = 0; j < maxw; ++j)
      g[j][0] = f[j][0];
    int k = 1;
    for (; (1 << k) <= W; ++k) {
      const bool bs = bool((1 << (k - 1)) & W);
      for (int j = 0; j < maxw; ++j)
        for (int s = 0; s <= j; ++s)
          letmax(g[j][k], f[j - s][k] + g[min(2 * s + bs, maxw - 1)][k - 1]);
    }
    cout << g[1][--k] << '\n';
  }
  return 0;
}
