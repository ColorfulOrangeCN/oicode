#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e5 + 1;
typedef long long inte;
int N;
inte A[maxn], B[maxn];
int main() {
  cin >> N;
  copy_n(istream_iterator<int>(cin), N, A + 1);
  partial_sum(A + 1, A + N + 1, A + 1);
  copy(A + 1, A + N + 1, B + 1);
  sort(B + 1, B + N + 1);
  if (B[1] < 0) {
    cout << -1 << endl;
    return 0;
  }
  for (int i = 1; i <= N; ++i)
    A[i] = lower_bound(B + 1, B + N + 1, A[i]) - B;
  inte ans = 0;
  for (int i = 1; i <= N; ++i) {
    while(A[i] != i) {
      swap(A[i], A[A[i]]);
      ++ans;
    }
  }
  cout << ans << endl;
  return 0;
}
