#include <bits/stdc++.h>
using namespace std;

constexpr int maxp = 16, maxn = 5e4 + 1;
int primes[maxp] = {2,  3,  5,  7,  11, 13, 17, 19,
                  23, 29, 31, 37, 41, 43, 47, 53};
double logp[maxp];
double f[maxp + 1][maxn];
int la[maxp + 1][maxn];
constexpr int maxb = 16000;
int number[maxb] = {1}, len = 0;
inline void mul(int x) {
  // cerr << x << endl;
  int v = 0;
  for (int i = 0; i <= len || v; ++i) {
    const int t = number[i] * x + v;
    v = t / 10;
    number[i] = t % 10;
    // cerr << number[i];
    len = max(len, i);
  }
  // cerr << endl;
}
int main() {
  int N;
  cin >> N;
  for (int i = 0; i < maxp; ++i)
    logp[i] = log(primes[i]);
  for (int i = 0; i <= maxp; ++i)
    for (int j = 1; j <= N; ++j)
      f[i][j] = 1e9;
  f[0][1] = 0;
  for (int i = 0; i < maxp; ++i) {
    for (int j = 1; j <= N; ++j) {
      for (int k = 0; j * (k + 1) <= N; ++k) {
        double &t = f[i + 1][j * (k + 1)];
        if (t > f[i][j] + k * logp[i]) {
          t = f[i][j] + k * logp[i];
          la[i + 1][j * (k + 1)] = k;
        }
      }
    }
  }
  int nc = N, cur = maxp;
  while (cur) {
    for (int j = 0; j < la[cur][nc]; ++j)
      mul(primes[cur - 1]);
    nc /= la[cur][nc] + 1;
    --cur;
  }
  while (len >= 0)
    cout << number[len--];
  cout << '\n';
  return 0;
}
