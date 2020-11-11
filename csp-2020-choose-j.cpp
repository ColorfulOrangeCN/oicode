#include <bits/stdc++.h>
using namespace std;
#define int long long
const static int maxn = 1e3 + 2;

int V[maxn][maxn];

int f[maxn][maxn], upper[maxn][maxn], lower[maxn][maxn];

signed main(signed argc, char *argv[])
{
    int N, M;
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> N >> M;
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= M; ++j)
            cin >> V[i][j];
    for (int j = 1; j <= M; ++j) {
        for (int i = 1; i <= N; ++i)
            upper[i][j] = upper[i - 1][j] + V[i][j];
        for (int i = N; i; --i)
            lower[i][j] = lower[i + 1][j] + V[i][j];
    }
    memset(f, -0x3f, sizeof(f));
    f[1][0] = 0;
    for (int j = 1; j <= M; ++j) {
        int maxv = -0x3f3f3f3f3f3f3f3f;
        for (int i = 1; i <= N; ++i) {
            maxv = max(maxv, f[i][j - 1] - upper[i - 1][j]);
            f[i][j] = max(f[i][j], upper[i][j] + maxv);
        }
        maxv = -0x3f3f3f3f3f3f3f3f;
        for (int i = N; i ; --i) {
            maxv = max(maxv, f[i][j - 1] - lower[i + 1][j]);
            f[i][j] = max(f[i][j], lower[i][j] + maxv);
        }
    }
    cout << f[N][M] << endl;
    return 0;
}
