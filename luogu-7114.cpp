#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = (2 << 20) + 4, maxc = 27;
typedef long long inte;
char S[maxn];
int N, z[maxn] = {};
inline void zfunc() {
  int l = 0, r = 0;
  memset(z, 0, sizeof(z));
  for (int i = 2; i <= N; ++i) {
    if (i <= r)
      z[i] = min(r - i + 1, z[i - l + 1]);
    while (i + z[i] <= N && S[z[i] + 1] == S[i + z[i]])
      ++z[i];
    if (i + z[i] + 1 > r) {
      r = i + z[i] - 1;
      l = i;
    }
  }
}
int num[maxc], cnt = 0, pre[maxn], suf[maxn];
void add(char c) {
  num[c - 'a'] ^= 1;
  if (num[c - 'a'])
    ++cnt;
  else
    --cnt;
}
void clnum() {
  memset(num, 0, sizeof(num));
  cnt = 0;
}
struct BIT {
  int c[maxc + 1];
  void clear() {
    memset(c, 0, sizeof(c));
  }
  inline int lowbit(int x) {return x & -x;}
  inline void add(int x) {
    while (x <= maxc) {
      ++c[x];
      x += lowbit(x);
    }
  }
  inline int ask(int x) {
    int res = 0;
    while (x) {
      res += c[x];
      x -= lowbit(x);
    }
    return res;   
  }
}bt;
int main(int argc, char *argv[])
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    cin >> (S + 1);
    N = strlen(S + 1);
    clnum();
    for (int i = 1; i <= N; ++i) {
      add(S[i]);
      pre[i] = cnt;
    }
    clnum();
    for (int i = N; i; --i) {
      add(S[i]);
      suf[i] = cnt;
    }
    zfunc();
    inte ans = 0;
    bt.clear();
    for (int i = 2; i < N; ++i) {
      bt.add(pre[i - 1] + 1);
      int k = z[i + 1] / i + 1;
      if (i * k == N)
        --k;
      ans += ((k + 1) / 2) * bt.ask(suf[i + 1] + 1);
      ans += (k / 2) * bt.ask(suf[1] + 1);
      // cerr << i << ' '<< k << ' ' << ans << endl;
    }
    cout << ans << '\n';
  }
  return 0;
}
