#include <bits/stdc++.h>
using namespace std;
typedef long long inte;
constexpr int maxn = 305;
inte C[maxn][maxn];
inte f[maxn][maxn];
int S[maxn];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int N, M, P;
    cin >> N >> M >> P;
    memset(C, 0, sizeof(C));
    memset(f, 0, sizeof(f));
    memset(S, 0, sizeof(S));
    // C[1][0] = C[1][1] = 1;
    C[0][0] = 1;
    for (int i = 1; i <= N; ++i) {
      C[i][0] = 1;
      for (int j = 1; j <= i; ++j)
        C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % P;
    }
    for (int i = 1; i <= M; ++i) {
      int p, q;
      cin >> p >> q;
      ++S[q];
    }
    bool flag = true;
    for (int i = N; i; --i)
      S[i] += S[i + 1], flag &= (S[i] <= N - i + 1);
    // cerr << S[1] << endl;
    if (!flag) {
      cout << "NO" << '\n';
      continue;
    }
    assert(S[1] == M);
    f[N + 1][0] = 1;
    for (int i = N; i; --i) {
      for (int j = 0; j + S[i] <= N - i + 1; ++j) {
        for (int k = 0; k <= j; ++k)
          (f[i][j] += f[i + 1][j - k] * C[j][k]) %= P;
      }
    }
    cout << "YES " << f[1][N - M] << '\n';
  }
  return 0;
}
