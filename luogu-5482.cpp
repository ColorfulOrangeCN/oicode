#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 2e6 + 5;
struct BIT {
  int c[maxn];
  inline int lowbit(int x) {return x & (-x);}
  inline void add(int x, int v) {
    x += 1e6 + 1;
    while (x < maxn) {
      c[x] += v;
      x += lowbit(x);
    }
  }
  inline int getsum(int x) {
    int res = 0;
    x += 1e6 + 1;
    while (x) {
      res += c[x];
      x -= lowbit(x);
    }
    return res;
  }
} btp, btb;
int cnt = 0;
constexpr int bound1 = 1e6 + 2, bound2 = 1e6 + 2;
int g[maxn], f[maxn];
inline void modify(int a, int b, int c, int v) {
  
}
tuple<int, int, int> p[maxn];
bool vis[maxn];
int main() {
  int N;
  cin >> N;
  int h = 0;
  for (int i = 1; i <= N; ++i) {
    string op;
    cin >> op;
    // cerr << i << endl;
    if (op == "Add") {
      int a, b, c;
      cin >> a >> b >> c;
      ++h;
      vis[h] = true;
      if (a == 0) {
        if (b > c)
          ++cnt, f[h] = 3;
      } else if (a < 0) {
        int x = ceil(double(c - b) / a);
        if (x > 1e6) {
          ++cnt, f[h] = 3;
          continue;
        } else if (x < -1e6) {
          continue;
        }
        f[h] = 1;
        g[h] = x;
        btb.add(x, 1);
      } else {
        int x = floor(double(c - b) / a);
        if (x > 1e6) {
          continue;
        } else if (x < -1e6) {
          ++cnt;
          f[h] = 3;
          continue;
        }
        g[h] = x;
        f[h] = 2;
        btp.add(x, 1);
      }
    } else if (op == "Del") {
      int x;
      cin >> x;
      if (vis[x]) {
        if (f[x] == 3) {
          --cnt;
        } else if (f[x] == 1) {
          btb.add(g[x], -1);
        } else if (f[x] == 2) {
          btp.add(g[x], -1);
        }
      }
      vis[x] = false;
    } else {
      int x;
      cin >> x;
      cout << cnt + btp.getsum(x - 1) + btb.getsum(1e6) - btb.getsum(x) << endl;
    }
  }
  return 0;
}
