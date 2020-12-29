#include <bits/stdc++.h>
using namespace std;
constexpr int limit = 1e9 + 7, maxn = 1e5 + 1;
typedef long long inte;
#define int long long
struct Segment {
  int l, r;
  mutable int v;
};
inline bool operator < (const Segment& a, const Segment& b) {
  return a.l < b.l;
}
typedef set<Segment> Cont;
Cont ct;
int seed;
inline int rnd() {return exchange(seed, (inte(7) * seed + 13) % limit);}
int a[maxn];
inline Cont::iterator split(int x) {
  Cont::iterator it = ct.lower_bound(Segment{x, 0, 0});
  if (it != ct.end() && it->l == x)
    return it;
  --it;
  int l = it->l, r = it->r, v = it->v;
  ct.erase(it);
  ct.insert(Segment{l, x - 1, v});
  return ct.insert(Segment{x, r, v}).first;
}
inline void assign(int l, int r, int x) {
  Cont::iterator itr = split(r + 1), itl = split(l);
  ct.erase(itl, itr);
  ct.insert(Segment{l, r, x});
}
template<typename T>
inline void perform(int l, int r, T func) {
  Cont::iterator itr = split(r + 1), itl = split(l);
  for (Cont::iterator it = itl; it != itr; ++it)
    func(it);
}
inline int fpow(int x, int p, int mods) {
  x %= mods;
  int res = 1;
  while (p) {
    if (p & 1)
      res = inte(res) * x % mods;
    x = inte(x) * x % mods;
    p >>= 1;
  }
  return res;
}
signed main() {
  int N, M, vmax;
  cin >> N >> M >> seed >> vmax;
  for (int i = 1; i <= N; ++i) {
    a[i] = rnd() % vmax + 1;
    ct.insert(Segment{i, i, a[i]});
  }
  for (int i = 1; i <= M; ++i) {
    int op = (rnd() % 4) + 1, l = rnd() % N + 1, r = rnd() % N + 1;
    if (l > r)
      swap(l, r);
    // cerr << i << ' ' << op << ' ' << l << ' ' << r << endl;
    if (op == 3) {
      int x = rnd() % (r - l + 1) + 1, t = 0;
      vector<pair<int, int>> segs;
      perform(l, r, [&](Cont::iterator it){segs.push_back(make_pair(it->v, it->r - it->l + 1));});
      sort(segs.begin(), segs.end());
      for (auto [v, c] : segs) {
        t += c;
        if (t >= x) {
          cout << v << '\n';
          break;
        }
      }
    } else {
      int x = rnd() % vmax + 1;
      if (op == 4) {
        int y = rnd() % vmax + 1;
        int ans = 0;
        perform(l, r, [&](Cont::iterator it) {(ans += inte(it->r - it->l + 1) * fpow(it->v, x, y) % y) %= y;});
        cout << ans << '\n';
      } else if (op == 1) {
        perform(l, r, [x](Cont::iterator it){it->v += x;});
      } else if (op == 2) {
        assign(l, r, x);
      }
    }
  }
  return 0;
}
