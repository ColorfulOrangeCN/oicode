#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 5e5 + 1;
int N;
struct BIT {
  int c[maxn];
  inline int lowbit(int x) { return x & -x; }
  void build() {
    for (int i = 1; i <= N; ++i) {
      cin >> c[i];
      for (int j = 1; j < lowbit(i); j *= 2)
        c[i] += c[i - j];
    }
  }
  void add(int x, int v) {
    while (x <= N) {
      c[x] += v;
      x += lowbit(x);
    }
  }
  int query(int l, int r) {
    --l;
    int res = 0;
    while (r > l)
      res += c[r], r -= lowbit(r);
    while (l > r)
      res -= c[l], l -= lowbit(l);
    return res;
  }
} bt;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int M;
  cin >> N >> M;
  bt.build();
  for (int i = 0; i < M; ++i) {
    int op, x, y;
    cin >> op >> x >> y;
    if (op == 1) {
      bt.add(x, y);
    } else {
      cout << bt.query(x, y) << '\n';
    }
  }
  return 0;
}
