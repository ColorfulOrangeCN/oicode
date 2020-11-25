#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e5 + 1;
template <typename T> T &letmax(T &l, const T &r) { return l < r ? l = r : l; }
struct BIT {
  int c[maxn];
  inline int lowbit(int x) { return x & -x; }
  void maxium(int x, int v) {
    while (x < maxn) {
      letmax(c[x], v);
      x += lowbit(x);
    }
  }
  int getmax(int x) {
    int res = 0;
    while (x) {
      letmax(res, c[x]);
      x -= lowbit(x);
    }
    return res;
  }
} bt;
typedef pair<int, int> Cookie;
Cookie cs[maxn];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int N;
  cin >> N;
  for (int i = 1; i <= N; ++i) {
    cin >> cs[i].second;
    cs[i].first = i - cs[i].second;
  }
  sort(cs + 1, cs + N + 1);
  int ans = 0;
  for (int i = 1; i <= N; ++i) {
    if (cs[i].first < 0)
      continue;
    const int res = bt.getmax(cs[i].second - 1) + 1;
    bt.maxium(cs[i].second, res);
    letmax(ans, res);
  }
  cout << ans << endl;
  return 0;
}
