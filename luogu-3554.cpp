#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 3e5 + 4;
int N;
vector<int> verts[maxn];
int f[maxn];
void dp(int u, int la, int r) {
  f[u] = 0;
  for (int v : verts[u]) {
    if (v == la)
      continue;
    dp(v, u, r);
    f[u] += f[v] + 1;
  }
  f[u] = max(f[u] - r, 0);
}
int main() {
  cin >> N;
  for (int i = 1; i < N; ++i) {
    int a, b;
    cin >> a >> b;
    verts[a].push_back(b);
    verts[b].push_back(a);
  }
  int L = 1, R = N - 1, ans = N - 1;
  while (L <= R) {
    const int mid = (L + R) / 2;
    dp(1, 0, mid);
    if (f[1] == 0) {
      R = mid - 1;
      ans = mid;
    } else {
      L = mid + 1;
    }
  }
  cout << ans << endl;
  return 0;
}
