#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e5 + 1;
typedef unsigned inte;
bool isnp[maxn];
int mu[maxn], pm[maxn], pcnt = 0, dv[maxn], ord[maxn];
struct BIT {
  inte c[maxn];
  inline int lowbit(int x){return x & (-x);}
  inline void add(int x, inte v) {
    while (x < maxn) {
      c[x] += v;
      x += lowbit(x);
    }
  }
  inte query(int l, int r) {
    --l;
    inte res = 0;
    while (r > l)
      res += c[r], r -= lowbit(r);
    while (l > r)
      res -= c[l], l -= lowbit(l);
    return res;
  }
} idt;
inline void predo() {
  mu[1] = 1;
  for (int i = 2; i < maxn; ++i) {
    if (!isnp[i]) {
      pm[++pcnt] = i;
      mu[i] = -1;
    }
    for (int j = 1; j <= pcnt && i * pm[j] < maxn; ++j) {
      isnp[i * pm[j]] = true;
      if (i % pm[j] == 0) {
        mu[i * pm[j]] = 0;
        break;
      } else {
        mu[i * pm[j]] = -mu[i];
      }
    }
  }
  for (int i = 1; i < maxn; ++i)
    for (int j = 1; i * j < maxn; ++j)
      dv[i * j] += i;
  iota(ord + 1, ord + maxn, 1);
  sort(ord + 1, ord + maxn, [&](int a, int b){return dv[a] < dv[b];});
}

tuple<int, unsigned, unsigned, int> ques[maxn / 5 + 1];
inte ans[maxn / 5 + 1];
int main() {
  int Q;
  predo();
  cin >> Q;
  for (int i = 0; i < Q; ++i) {
    auto &[a, n, m, id] = ques[i];
    id = i;
    cin >> n >> m >> a;
  }
  sort(ques, ques + Q);
  int R = 1;
  for (int i = 0; i < Q; ++i) {
    auto [a, n, m, id] = ques[i];
    while (dv[ord[R]] <= a) {
      const int x = ord[R++];
      for (int k = 1; x * k < maxn; ++k)
        idt.add(x * k, dv[x] * mu[k]);
    }
    if (n > m)
      swap(n, m);
    for (int l = 1, r; l <= n; l = r + 1) {
      r = min(n / (n / l), m / (m / l));
      ans[id] += (n / l) * (m / l) * idt.query(l, r);
    }
  }
  for (int i = 0; i < Q; ++i)
    cout << (ans[i] & (~0u >> 1)) << '\n';
}
