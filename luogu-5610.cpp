#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e5 + 5;
typedef long long inte;

struct Read {
  template<typename T> inline const Read& operator()(T &x) const {
    x = 0;
    static char c = 0;
    while (!isdigit(c))
      c = getchar();
    while (isdigit(c)) {
      x *= 10;
      x += c - '0';
      c = getchar();
    }
    return *this;
  }
} read;
int N, a[maxn];

struct BIT {
  inte c[maxn];
#define lowbit(x) ((x) & (-(x)))
  inline void build() {
    for (int i = 1; i <= N; ++i) {
      read(a[i]);
      c[i] = a[i];
      const int t = lowbit(i);
      for (int j = 1; j < t; j <<= 1)
        c[i] += c[i - j];
    }
  }
  inline void add(int x, int v) {
    while (x <= N) {
      c[x] += v;
      x += lowbit(x);
    }
  }
  inline inte query(int l, int r) {
    --l;
    inte res = 0;
    while (r > l)
      res += c[r], r -= lowbit(r);
    while (l > r)
      res -= c[l], l -= lowbit(l);
    return res;
  }
} bt;
int buf[400 * maxn], newp = 0;
struct Cache {
  int *l, *r;
  inline void resize(int v) {
    l = buf + newp;
    newp += v;
    r = buf + newp;
  }
  inline int* begin() {return l;}
  inline int* end() {return r;}
  inline int size() const {return r - l;}
  inline int& operator[] (int x) {return l[x];}
};
struct SCache : Cache {
  int c;
  void push_back(int x) {
    // cerr << c << endl;
    l[c++] = x;
  }
};
SCache gug[5 * maxn];
Cache skp[5 * maxn];
int step(int i, int j) {
  if (j >= skp[i].size() || a[gug[i][j]] % i == 0)
    return j;
  else
    return skp[i][j] = step(i, skp[i][j]);
}
int cnt[5 * maxn];
signed main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  int M;
  read(N)(M);
  bt.build();
  for (int i = 1; i <= N; ++i) {
    ++cnt[a[i]];
    for (int j = 2; j * j <= a[i]; ++j) {
      if (a[i] % j == 0) {
        ++cnt[j];
        if (j * j != a[i])
          ++cnt[a[i] / j];
      }
    }
  }
  for (int i = 1; i < 5 * maxn; ++i)
    gug[i].resize(cnt[i]);
  for (int i = 1; i <= N; ++i) {
    gug[a[i]].push_back(i);
    for (int j = 2; j * j <= a[i]; ++j) {
      if (a[i] % j == 0) {
        gug[j].push_back(i);
        if (j * j != a[i])
          gug[a[i] / j].push_back(i);
      }
    }
  }
  for (int i = 2; i < 5 * maxn; ++i) {
    skp[i].resize(gug[i].size());
    for (int j = 0; j < skp[i].size(); ++j)
      skp[i][j] = j + 1;
  }
  inte lastans = 0;
  while (M--) {
    inte op, l, r;
    read(op)(l)(r);
    l ^= lastans;
    r ^= lastans;
    if (op == 1) {
      inte x;
      read(x);
      x ^= lastans;
      if (x == 1 || !skp[x].size())
        continue;
      l = lower_bound(gug[x].begin(), gug[x].end(), l) - gug[x].begin();
      r = lower_bound(gug[x].begin(), gug[x].end(), ++r) - gug[x].begin();
      // cerr << l << ' ' << r << endl;
      for (int i = step(x, l); i < r; i = step(x, ++i)) {
        const int t = gug[x][i];
        bt.add(t, a[t] / x - a[t]);
        a[t] /= x;
      }
    } else {
      printf("%lld\n", lastans = bt.query(l, r));
    }
  }
  return 0;
}
