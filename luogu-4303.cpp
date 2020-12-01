template <typename T> T& letmax(T& l, const T& r) { return l < r ? l = r : l; }
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> Meta;
constexpr int maxn = 20000;
int pos[maxn + 1][5], cnt[maxn + 1], N;
struct BIT {
  int c[maxn * 5 + 1];
  inline int lowbit(int x) { return x & -x; }
  void maxium(int x, int v) {
    while (x <= 5 * N) {
      letmax(c[x], v);
      x += lowbit(x);
    }
  }
  int query(int x) {
    int res = 0;
    while (x) {
      letmax(res, c[x]);
      x -= lowbit(x);
    }
    return res;
  }
} bt;
int main() {
  ios::sync_with_stdio(false);
  cin >> N;
  for (int i = 0, x; i < 5 * N; ++i) {
    cin >> x;
    pos[x][cnt[x]++] = i;
  }
  for (int i = 0, y; i < 5 * N; ++i) {
    cin >> y;
    for (int j = 4; j >= 0; --j)
      bt.maxium(pos[y][j] + 1, bt.query(pos[y][j]) + 1);
  }
  cout << bt.query(5 * N) << '\n';
  return 0;
}
