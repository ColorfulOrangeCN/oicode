#include <bits/stdc++.h>
using namespace std;
typedef long long inte;
extern "C" void MinMax(inte s, inte t, inte *mn, inte *mx);
extern "C" inte findGap(int T, int N);
constexpr int maxn = 1e5 + 5;
inte findGap(int T, int N) {
  if (T == 1) {
    static inte A[maxn];
    inte ans = 0;
    A[0] = -1;
    A[N + 1] = 1000000000000000010ll;
    for (int i = 1; i <= (N + 1) >> 1; ++i)
      MinMax(A[i - 1] + 1, A[N - i + 2] - 1, &A[i], &A[N - i + 1]);
    for (int i = 1; i < N; i++)
      ans = max(ans, A[i + 1] - A[i]);
    return ans;
  }
  inte l, r;
  MinMax(0, 1e18, &l, &r);
  inte box = (ceil)(((double)r - l) / (N - 1) - 1e-9);
  inte la = l++;
  inte ans = 0;
  while (l <= r) {
    inte a, b;
    MinMax(l, l + box, &a, &b);
    ans = max(ans, a - la);
    if (b != -1)
      la = b;
    l += box + 1;
  }
  return ans;
}
