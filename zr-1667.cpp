#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 2e5 + 1;
int A[maxn];
int premax[int(2e6 + 2)];
int main() {
  int N;
  cin >> N;
  copy_n(istream_iterator<int>(cin), N, A);
  sort(A, A + N);
  N = unique(A, A + N) - A;
  int ans = 0;
  for (int i = 0; i < N; ++i)
    premax[A[i]] = A[i];
  for (int i = 1; i <= 1e6; ++i)
    premax[i] = max(premax[i], premax[i - 1]);
  for (int i = 0; i < N; ++i)
    for (int j = 2; A[i] * j <= 2e6; ++j)
      ans = max(ans, premax[A[i] * j - 1] % A[i]);
  cout << ans << endl;
  return 0;
}
