#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 5000010, mods = 998244353;
int n, T;
char s[maxn], ans[maxn];
long long pre[maxn];
int main() {
  cin >> T >> (s + 1);
  n = strlen(s + 1);
  deque<int> q;
  for (int i = 1; i <= T; ++i)
    q.push_back(i);
  int r = 0, dep = 0;
  for (int i = 1; i <= n; ++i)  {
    ans[i] = '0';
    r += s[i] - '0';
    if (s[i] == '0')
      pre[0] += r;
  }
  for (int i = 1, c = 0; i <= n; ++i) {
    if (s[i] == '0') {
      ++c;
      continue;
    }
    q.push_front(1 - (++dep));
    while (q.back() + dep > T)
      q.pop_back();
    for (int j = 0; j < c && !q.empty(); ++j) {
      const int cur = q.front() + dep;
      ++pre[cur];
      if (cur + r <= T)
        --pre[cur + r];
      q.pop_front();
    }
    c = 0;
    --r;
    ans[i + q.size() - T] = '1';
  }
  cout << (ans + 1) << '\n';
  partial_sum(pre + 1, pre + T + 1, pre + 1);
  partial_sum(pre, pre + T + 1, pre);
  long long sum = 0, cp = 1;
  for (int i = 0; i <= T; ++i) {
    // cerr << pre[i] << endl;
    sum ^= pre[i] % mods * cp % mods;
    (cp *= 233) %= mods;
  }
  cout << sum << '\n';
  return 0;
}
