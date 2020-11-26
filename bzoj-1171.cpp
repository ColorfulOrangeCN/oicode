#ifndef _FOL_UTILITY_
#define _FOL_UTILITY_

namespace fol {

  template <typename T>
  T exchange(T& l, const T& r) {
    T tmp = l;
    l = r;
    return tmp;
  }

  template <typename T>
  T& letmax(T& l, const T& r) {
    return l < r ? l = r : l;
  }

  template <typename T>
  T& letmin(T& l, const T& r) {
    return r < l ? l = r : l;
  }

}  // namespace fol

#endif

#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 5e5 + 1, inf = ~0u>>2;
using fol::letmin;
int memcnt = 0;
struct SegmentTree {
  typedef pair<int, int> Meta;
  struct Segment {
    int val;
    deque<Meta> q;
    Segment() : val(inf) {}
    inline int front() { return q.empty() ? inf : q.front().first; }
    inline void push(Meta v) {
      while (!q.empty() && q.back().first >= v.first)
        q.pop_back();
      q.push_back(v);
    }
    inline void filter(int lim) {
      while (!q.empty() && q.front().second < lim)
        q.pop_front();
      ++memcnt;
      if (memcnt >= 10000)
        q.shrink_to_fit();
    }
  } segs[maxn * 4];
#define lc (k * 2)
#define rc (lc + 1)
  inline void maintain(int k, int l, int r) {
    segs[k].val = segs[k].front();
    if (l != r) {
      letmin(segs[k].val, segs[lc].val);
      letmin(segs[k].val, segs[rc].val);
    }
  }
  void insert(int k, int l, int r, int L, int R, Meta v) {
    if (l > R || r < L)
      return;
    if (L <= l && r <= R) {
      segs[k].push(v);
    } else {
      const int mid = (l + r) / 2;
      insert(lc, l, mid, L, R, v);
      insert(rc, mid + 1, r, L, R, v);
    }
    maintain(k, l, r);
  }
  void remove(int k, int l, int r, int L, int R, int lim) {
    if (l > R || r < L)
      return;
    if (L <= l && r <= R) {
      segs[k].filter(lim);
    } else {
      const int mid = (l + r) / 2;
      remove(lc, l, mid, L, R, lim);
      remove(rc, mid + 1, r, L, R, lim);
    }
    maintain(k, l, r);
  }
  int query(int k, int l, int r, int L, int R) {
    if (l > R || r < L)
      return inf;
    // cerr << l << ' ' << r << segs[k].front()<< endl;
    if (L <= l && r <= R) {
      return segs[k].val;
    } else {
      const int mid = (l + r) / 2;
      return min({segs[k].front(), query(lc, l, mid, L, R), query(rc, mid + 1, r, L, R)});
    }
  }
} segt;
typedef SegmentTree::Meta SMeta;
int X[maxn], Y[maxn], ll[maxn];
int plc[maxn];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  // freopen("t.in", "r", stdin);
  int N, l;
  cin >> N >> l;
  // cerr << sizeof(segt) << endl;
  int tot = 0;
  for (int i = 2; i <= N; ++i) {
    cin >> X[i] >> Y[i] >> ll[i];
    plc[++tot] = X[i];
    plc[++tot] = Y[i];
  }
  sort(plc + 1, plc + tot + 1);
  auto tf = [&](int x) { return lower_bound(plc + 1, plc + tot + 1, x) - plc; };
  transform(X + 2, X + N + 1, X + 2, tf);
  transform(Y + 2, Y + N + 1, Y + 2, tf);
  X[1] = 1;
  Y[1] = tot;
  segt.insert(1, 1, tot, X[1], Y[1], SMeta(0, 0));
  int L = 1;
  for (int i = 2; i <= N; ++i) {
    while (ll[L] < ll[i] - l)
      segt.remove(1, 1, tot, X[L], Y[L], ll[i] - l), ++L;
    const int ans = segt.query(1, 1, tot, X[i], Y[i]) + 1;
    segt.insert(1, 1, tot, X[i], Y[i], SMeta(ans, ll[i]));
    if (ans >= inf)
      cout << -1 << '\n';
    else
      cout << ans << '\n';
  }
  return 0;
}
