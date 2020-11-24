#include <bits/stdc++.h>
using namespace std;
constexpr int maxv = 1e4 + 1, maxn = 101;
int f[maxv], p[maxn][maxn];
int main() {
    int T, N, M;
    cin >> T >> N >> M;
    for (int i = 1; i <= T; ++i)
        for (int j = 1; j <= N; ++j)
            cin >> p[i][j];
    for (int i = 1; i < T; ++i) {
        memset(f, 0, sizeof(f));
        for (int k = 1; k <= N; ++k)
            for (int j = p[i][k]; j <= M; ++j)
                f[j] = max(f[j], f[j - p[i][k]] + p[i + 1][k] - p[i][k]);
        M += f[M];
    }
    cout << M << endl;
}
