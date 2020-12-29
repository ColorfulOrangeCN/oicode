#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e6 + 2;
typedef long long inte;
struct BIT {
  inte c[maxn];
  inline int lowbit(int x) {return x & (-x);}
  void add(int x, int v) {
    while (x < maxn) {
      c[x] += v;
      x += lowbit(x);
    }
  }
  inte query(int x) {
    inte res = 0;
    while (x) {
      res += c[x];
      x -= lowbit(x);
    }
    return res;
  }
} sum, cnt;
int arr[maxn];
int plc[maxn];
typedef tuple<char, int, int> Command;
Command ops[maxn];
int main() {
  int N, M;
  cin >> N >> M;
  int tot = 1;
  for (int i = 1; i <= M; ++i) {
    auto &[c, a, b] = ops[i];
    cin >> c >> a >> b;
    plc[tot++] = b;
  }
  sort(plc, plc + tot);
  cnt.add(1, N);
  for (int i = 1; i <= M; ++i) {
    auto [c, a, b] = ops[i];
    if (c == 'U') {
      b = lower_bound(plc, plc + tot, b) - plc;
      // cerr << b << endl;
      sum.add(b + 1, plc[b]);
      sum.add(arr[a] + 1, -plc[arr[a]]);
      cnt.add(b + 1, 1);
      cnt.add(arr[a] + 1, -1);
      arr[a] = b;
    } else {
      const int ind = lower_bound(plc, plc + tot, b) - plc;
      // cerr << ind << ' ' << sum.query(ind + 1) << endl;
      cout << (((N - cnt.query(ind + 1)) * b + sum.query(ind + 1) >= inte(a) * b) ? "TAK" : "NIE") << '\n';
    }
  }
  return 0;
}
