#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 51, maxm = 5001, delta = 2500, inf = 0x3f3f3f3f;
int f[maxn][maxm];
int a[maxn], b[maxn], w[maxn][maxn];
int main(int argc, char *argv[])
{
    memset(f, -0x3f, sizeof(f));
    f[0][delta] = 0;
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> a[i] >> b[i];
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            cin >> w[j][i];
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
            for (int k = 0; k < maxm; ++k) {
                if (k - a[i] >= 0 && k - a[i] < maxm)
                    f[i][k] = max(f[j][k - a[i]] + b[i] + w[i][j], f[i][k]);
            }
        }
    }
    int ans = -inf;
    for (int i = 1; i <= n; ++i)
        ans = max(ans, f[i][m + delta]);
    if (ans <= -inf / 2)
        cout << -1 << endl;
    else
        cout << ans << endl;
    return 0;
}
