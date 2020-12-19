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
constexpr int maxn = 1e5 + 1;
#define int long long
int f[maxn];
int a[maxn], b[maxn];
signed main() {
  int N;
  cin >> N;
  for (int i = 1; i <= N; ++i)
    cin >> a[i] >> b[i];
  if (a[1] == b[1] && N == 1) {
    cout << "-1\n";
    return 0;
  }
  sort(a + 1, a + N + 1);
  sort(b + 1, b + N + 1);
  memset(f, 0x3f, sizeof(f));
  f[0] = 0;
  for (int i = 1; i <= N; ++i) {
    if (a[i] != b[i])
      letmin(f[i], f[i - 1] + abs(a[i] - b[i]));
    if (i >= 2)
      letmin(f[i], f[i - 2] + abs(a[i] - b[i - 1]) + abs(a[i - 1] - b[i]));
    if (i >= 3) {
      letmin(f[i], f[i - 3] + abs(a[i - 2] - b[i]) + abs(b[i - 2] - a[i - 1]) + abs(a[i] - b[i - 1]));
      letmin(f[i], f[i - 3] + abs(a[i] - b[i - 2]) + abs(a[i - 1] - b[i]) + abs(a[i - 2] - b[i - 1]));
      if (a[i - 1] == b[i - 1])
        letmin(f[i], f[i - 3] + abs(a[i] - b[i - 2]) + abs(b[i] - a[i - 2]) + abs(a[i - 1] - b[i - 1]));
    }
  }
  cout << f[N] << endl;
  return 0;
}
