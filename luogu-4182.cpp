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
using namespace fol;
#endif

#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e5 + 9, maxk = 109;
typedef pair<int, int> Reg;
Reg rgs[maxn], tmp[maxn];
int g[maxn];
int f[maxn][maxk];
struct MQ {
  pair<int, int> q[maxk + 1];
  int h, t;
  MQ() : h(1), t(0) {}
  bool empty() {return h > t;}
  int back() { return q[t].first; }
  int front() { return q[h].first; }
  void check(int lim) {
    while (h <= t && q[h].second <= lim)
      ++h;
  }
} qs[maxn];
bool bk[maxn] = {};
bool comp(Reg a, Reg b) {return a.first != b.first ? a.first < b.first : a.second > b.second;}
signed main() {
  int N, K;
  cin >> N >> K;
  int ansK = K;
  for (int i = 1; i <= N; ++i)
    cin >> tmp[i].first >> tmp[i].second;
  sort(tmp + 1, tmp+ N + 1, comp);
  int q1 = 1, maxR = -1, tot = 0;
  for (int i = 1; i <= N; ++i) {
    if (tmp[i].second > maxR) {
      rgs[++tot] = tmp[i];
      maxR = tmp[i].second;
    } else {
      --ansK;
    }
  }
  N = tot;
  for (int i = 1; i <= N; ++i) {
    maxR = rgs[i].second;
    // cerr << rgs[i].first << ' ' << rgs[i].second << endl;
    while (q1 < i && rgs[q1].second <= rgs[i].first) {
      for (int k = 0; k < q1 && k <= K; ++k) {
        letmax(g[q1 - k], f[q1][k]);
        qs[q1 - k].check(q1);
      }
      ++q1;
    }
    for (int j = 0; j < i && j <= K; ++j) {
      const int vab = i - j;
      letmax(f[i][j], g[vab - 1] + rgs[i].second - rgs[i].first);
      if (!qs[vab - 1].empty())
        letmax(f[i][j], qs[vab - 1].front() + rgs[i].second);
      MQ& curq = qs[vab];
      while (!curq.empty() && curq.back() <= f[i][j] - rgs[i].second)
        --curq.t;
      curq.q[++curq.t] = make_pair(f[i][j] - rgs[i].second, i);
    }
  }
  // for (int i = 1; i <= N; ++i)
    // cerr << f[i][0] << endl;
  int ans = 0;
  for (int i = 1; i <= N; ++i)
    letmax(ans, f[i][max(ansK - N + i, 0)]);
  cout << ans << endl;
  return 0;
}
