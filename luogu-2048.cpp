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
constexpr int maxn = 5e5 + 1, lgn = 21;
typedef long long inte;
constexpr inte inf = 0x7fffffffffffffff;
int presum[maxn];
typedef pair<inte, int> Plc;
Plc st[maxn][lgn];
int logger[maxn];
  int N, K, L, R;
struct Segment {
  int s, l, r;
  Plc v;
  Segment(int _s, int _l, int _r) : s(_s), l(_l), r(_r) {
    l = max(s + L - 1, l);
    r = min(r, min(s + R - 1, N));
    const int len = (r - l + 1);
    assert(len <= N);
    if (len > 0)
      v = max(st[l][logger[len]], st[r - (1 << logger[len]) + 1][logger[len]]),
        v.first -= presum[s - 1];
    else
      v = Plc(-inf, 0);
    // cerr << "ADD " << s << ' ' << l << ' ' << r << ' ' << v.first << endl;
  }
  Segment(const Segment& x) = default;
};
bool operator < (Segment a, Segment b) { return a.v < b.v; }
int main() {
  // freopen("t.in", "r", stdin);
  memset(st, -1, sizeof(st));
  cin >> N >> K >> L >> R;
  copy_n(istream_iterator<inte>(cin), N, presum + 1);
  partial_sum(presum + 1, presum + N + 1, presum + 1);
  for (int i = 1; i <= N; ++i)
    st[i][0] = Plc(presum[i], i);
  for (int i = 2; i <= N; ++i)
    logger[i] = logger[i >> 1] + 1;
  for (int k = 0; k < logger[N]; ++k)
    for (int i = 1; i + (1 << k) <= N; ++i)
      st[i][k + 1] = max(st[i + (1 << k)][k], st[i][k]);
  priority_queue<Segment> q;
  for (int i = 1; i <= N; ++i)
      q.push(Segment(i, 0, N));
  // cerr << "DEBUG" << q.empty() << endl;
  inte ans = 0;
  for (int i = 0; i < K; ++i) {
    // cerr << "DEBUG" << endl;
    // assert(!q.empty());
    Segment t = q.top();
    // cerr << t.s << ' ' << t.l << ' ' << t.r << ' ' << t.v.second << ' ' << t.v.first << endl;
    q.pop();
    ans += t.v.first;
    q.push(Segment(t.s, t.l, t.v.second - 1));
    q.push(Segment(t.s, t.v.second + 1, t.r));
  }
  cout << ans << endl;
  return 0;
}
