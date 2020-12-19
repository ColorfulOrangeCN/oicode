#include <bits/stdc++.h>
using namespace std;

typedef long long inte;
constexpr int maxn = 1e6;
inte a[maxn], b[maxn];

int main() {
  int N;
  cin >> N;
  copy_n(istream_iterator<int>(cin), N, a);
  copy_n(istream_iterator<int>(cin), N, b);
  sort(a, a + N);
  sort(b, b + N);
  inte ans = 0;
  for (int i = 0; i < N; ++i)
    ans += a[i] * b[i];
  cout << ans << endl;
  return 0;
}
