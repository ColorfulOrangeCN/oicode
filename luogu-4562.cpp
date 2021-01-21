#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e7 + 1, mods = 1e9 + 7;
typedef long long inte;
bool vis[maxn];
int main() {
  int l, r;
  cin >> l >> r;
  inte sum = 0;
  for (int i = l; i <= r; ++i) {
    if (!vis[i - l]) {
      ++sum;
      for (int j = 2; i * j <= r; ++j)
        vis[i * j - l] = true;
    }
  }
  inte ans = sum;
  for (int i = 1; i <= (r - l + 2); ++i)
    if (i != sum + 1)
      (ans *= i) %= mods;
  cout << ans << '\n';
  return 0;
}
