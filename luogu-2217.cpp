#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 10;
double f[maxn][maxn][maxn][maxn][maxn];
bool vis[maxn][maxn][maxn][maxn][maxn];
int val[maxn][maxn];
inline int getsum(int a, int b, int c, int d) {
  int res = 0;
  for (int i = a; i <= b; ++i)
    for (int j = c; j <= d; ++j)
      res += val[i][j];
  return res;
}
double ave = 0;
inline double p2(double x) { return x * x; }
double dfs(int a, int b, int c, int d, int k) {
  if (vis[a][b][c][d][k])
    return f[a][b][c][d][k];
  vis[a][b][c][d][k] = true;
  double res = 1e18;
  if (k == 1) {
    res = p2(getsum(a, b, c, d) - ave);
  } else {
    for (int s = 1; s < k; ++s) {
      for (int i = a; i < b; ++i)
        res = min(res, dfs(a, i, c, d, s) + dfs(i + 1, b, c, d, k - s));
      for (int i = c; i < d; ++i)
        res = min(res, dfs(a, b, c, i, s) + dfs(a, b, i + 1, d, k - s));
    }
  }
  return f[a][b][c][d][k] = res;
}

int main() {
  int A, B, N;
  cin >> A >> B >> N;
  for (int i = 0; i < A; ++i)
    for (int j = 0; j < B; ++j)
      cin >> val[i][j], ave += val[i][j];
  ave /= N;
  // cerr << ave << endl;
  cout << fixed << setprecision(2) << sqrt(dfs(0, A - 1, 0, B - 1, N) / N) << '\n';
  return 0;
}
