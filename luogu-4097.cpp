#include <bits/stdc++.h>
using namespace std;
typedef pair<double, double> Line;
inline double cut(Line l, int x) {
  return l.first * x + l.second;
}
inline Line gen(int xa, int ya, int xb, int yb) {
  assert(xb != xa);
  const double k = (yb - ya) / double(xb - xa);
  return Line(k, ya - xa * k);
}
constexpr int maxn = 1e5 + 2;
constexpr int maxv = 39989;
typedef pair<double, int> Decision;
struct LCT {
  static constexpr int maxc = maxn * 4;
  Line nl[maxc];
  int id[maxc];
#define lc (k * 2)
#define rc (lc + 1)
#define cutid(id) (cut(line, (id)) > cut(nl[k], (id)))
#define goleft(line, cid) (insert(lc, l, mid, L, min(mid, R), line, cid))
#define goright(line, cid)  (insert(rc, mid + 1, r, max(L, mid + 1), R, line, cid))
  void insert(int k, int l, int r, int L, int R, Line line, int cid) {
    // if (r < L || l > R)
    // return;
    // cerr << l << ' ' << r << ' ' << L << ' ' << R << endl;
    const int mid = (l + r) / 2;
    if (L <= l && r <= R) {
      const bool isl = cutid(L), ism = cutid(mid), isr = cutid(R);
      if (ism) {
        if (!isr)
          goright(nl[k], id[k]);
        else if (!isl)
          goleft(nl[k], id[k]);
        nl[k] = line;
        id[k] = cid;
      } else {
        if (isl)
          goleft(line, cid);
        else
          goright(line, cid);
      }
    } else {
      if (L <= mid)
        goleft(line, cid);
      if (R >= mid + 1)
        goright(line, cid);
    }
  }
  Decision query(int k, int l, int r, int p) {
    const int mid = (l + r) / 2;
    const auto cur = make_pair(cut(nl[k], p), -id[k]);
    if (l == r)
      return cur;
    if (p <= mid)
      return max(cur, query(lc, l, mid, p));
    else if (p > mid)
      return max(cur, query(rc, mid + 1, r, p));
    else
      return cur;
  }
} segt;
Decision lp[maxv + 1];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int N;
  cin >> N;
  int cnt = 0, lastans = 0;
  for (int i = 1; i <= N; ++i) {
    int op;
    cin >> op;
    if (op) {
      int x0, y0, x1, y1;
      cin >> x0 >> y0 >> x1 >> y1;
      x0 = (x0 + lastans - 1) % maxv + 1;
      x1 = (x1 + lastans - 1) % maxv + 1;
      y0 = (y0 + lastans - 1) % int(1e9) + 1;
      y1 = (y1 + lastans - 1) % int(1e9) + 1;
      ++cnt;
      if (x0 > x1) {
        swap(x0, x1);
        swap(y0, y1);
      }
      if (x0 == x1)
        lp[x0] = max(lp[x0], Decision(max(y1, y0), cnt));
      else
        segt.insert(1, 1, maxv, x0, x1, gen(x0, y0, x1, y1), cnt);
    } else {
      int k;
      cin >> k;
      k = (k + lastans - 1) % maxv + 1;
      cout << (lastans = -max(segt.query(1, 1, maxv, k), lp[k]).second) << '\n';
    }
  }
  return 0;
}
