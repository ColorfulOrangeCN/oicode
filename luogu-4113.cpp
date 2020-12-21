#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 2e6 + 2;
struct Bit {
  int c[maxn];
  inline int lowbit(int x) {
    return x & (-x);
  }
  void add(int x, int v) {
    while (x < maxn) {
      c[x] += v;
      x += lowbit(x);
    }
  }
  int query(int x) {
    int res = 0;
    while (x) {
      res += c[x];
      x -= lowbit(x);
    }
    return res;
  }
  void addr(int l, int r, int v) {
    add(l, v);
    add(r + 1, -v);
  }
} bt;

int la[maxn][2];
int N, C, M;
int x[maxn];
struct Que {
  int l, r, id;
} qs[maxn];
int ans[maxn];
bool operator < (Que a, Que b) {
  return a.r < b.r;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> N >> C >> M;
  copy_n(istream_iterator<int>(cin), N, x + 1);
  for (int i = 0; i < M; ++i) {
    cin >> qs[i].l >> qs[i].r;
    qs[i].id = i;
  }
  sort(qs, qs + M);
  int R = 1;
  for (int i = 0; i < M; ++i) {
    while (R <= qs[i].r) {
      const int i = x[R];
      if (la[i][0])
        bt.addr(la[i][1] + 1, la[i][0], 1);
      la[i][1] = la[i][0];
      la[i][0] = R;
      ++R;
    }
    // cerr << qs[i].l << ' ' << qs[i].r << endl;
    ans[qs[i].id] = bt.query(qs[i].l);
  }
  copy(ans, ans + M, ostream_iterator<int>(cout, "\n"));
  return 0;
}
