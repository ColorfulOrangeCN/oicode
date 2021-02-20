#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e5 + 4;
#define int long long
typedef long long inte;
inte ht[maxn];
inte H[maxn], A[maxn];
int N, M, K, P;
inline bool check(inte maxH) {
  fill(ht, ht + maxn, maxH);
  priority_queue<pair<inte, int>, vector<pair<inte, int>>, greater<pair<inte, int>>> pq;
  for (int i = 1; i <= N; ++i)
    if (ht[i] - M * A[i] < H[i])
      pq.push(make_pair(ht[i] / A[i], i));
  for (int i = 1; i <= M; ++i) {
    for (int j = 1; j <= K; ++j) {
      if (pq.empty())
        return true;
      pair<inte, int> c = pq.top();
      pq.pop();
      if (c.first < i)
        return false;
      ht[c.second] += P;
      c.first = ht[c.second] / A[c.second];
      if (ht[c.second] - M * A[c.second] < H[c.second])
        pq.push(c);
    }
  }
  return pq.empty();
}

signed main() {
  cin >> N >> M >> K >> P;
  for (int i = 1; i <= N; ++i)
    cin >> H[i] >> A[i];
  inte L = 0, R = 1ll << 60, ans = 0;
  while (L <= R) {
    const inte mid = (L + R) / 2;
    if (check(mid)) {
      R = mid - 1;
      ans = mid;
    } else {
      L = mid + 1;
    }
  }
  cout << ans << endl;
  return 0;
}
