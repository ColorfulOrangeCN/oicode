#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 2e5 + 2;
constexpr double inf = 1e9;
int cur[maxn], l[maxn], p[maxn];
inline double pickOne(int tp) {
  if (cur[tp] >= l[tp])
    return -inf;
  return p[tp] * (-double(cur[tp]) / (cur[tp] + l[tp]) + double(cur[tp] + 1) / (cur[tp] + 1 + l[tp]));
}
inline double throwOne(int tp) {
  if (cur[tp] == 0)
    return -inf;
  return p[tp] * (double(cur[tp] - 1) / (cur[tp] - 1 + l[tp]) - double(cur[tp]) / (cur[tp] + l[tp]));
}
typedef pair<double, int> Pair;
set<Pair, greater<Pair>> st, rc;
inline void remove(int qi) {
  st.erase(make_pair(pickOne(qi), qi));
  rc.erase(make_pair(throwOne(qi), qi));
}
inline void extend(int qi) {
  st.insert(make_pair(pickOne(qi), qi));
  rc.insert(make_pair(throwOne(qi), qi));
}
int T;
double ans = 0;
inline void getSome() {
  while (T) {
    assert(!st.empty());
    auto it = st.begin();
    const int qi = it->second;
    if (it->first < 0)
      break;
    ans += it->first;
    remove(qi);
    ++cur[qi];
    extend(qi);
    // cerr <<"fake " << qi << ' ' << cur[qi] << ' ' << ans << endl;
    --T;
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, q;
  cin >> n >> T >> q;
  copy_n(istream_iterator<int>(cin), n, p + 1);
  copy_n(istream_iterator<int>(cin), n, l + 1);
  for (int i = 1; i <= n; ++i)
    st.insert(make_pair(pickOne(i), i));
  for (int i = 1; i <= n; ++i)
    rc.insert(make_pair(throwOne(i), i));
  getSome();
  while (q--) {
    int qi, v;
    cin >> v >> qi;
    v = (v == 1) ? 1 : -1;
    ans -= p[qi] * double(cur[qi]) / (cur[qi] + l[qi]);
    remove(qi);
    l[qi] += v;
    if (cur[qi]) {
      --cur[qi];
      ++T;
    }
    extend(qi);
    ans += p[qi] * double(cur[qi]) / (cur[qi] + l[qi]);
    // cerr << ans << endl;
    getSome();
    while (st.begin()->first + rc.begin()->first > 0) {
      ans += st.begin()->first + rc.begin()->first;
      // cerr << ans << endl;
      const int tin = st.begin()->second, tout = rc.begin()->second;
      remove(tin);
      remove(tout);
      ++cur[tin];
      --cur[tout];
      extend(tin);
      extend(tout);
    }
    cout << fixed << setprecision(7) << ans << '\n';
  }
  return 0;
}
