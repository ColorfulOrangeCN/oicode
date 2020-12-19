#include <bits/stdc++.h>
using namespace std;
typedef long long inte;
constexpr int maxn = 3e5 + 1, mods = 1e9 + 7;
inte val[maxn], we[maxn];
int main() {
  int N;
  cin >> N;
  copy_n(istream_iterator<inte>(cin), N, we + 1);
  copy_n(istream_iterator<inte>(cin), N, val + 1);
  partial_sum(we + 1, we + N + 1, we + 1);
  partial_sum(val + 1, val + N + 1, val + 1);
  inte ans = 0;
  for (int i = 1; i <= N; ++i)
    (ans += we[i] % mods * (val[i] - val[N - i])) %= mods;
  cout << (ans + mods) % mods << '\n';
  return 0;
}
