#include <bits/stdc++.h>
using namespace std;
const static int maxn = 101 + 1;
int f[maxn * 2][maxn * 2], g[maxn * 2][maxn * 2];
int A[maxn * 2], pre[maxn * 2];
int main(int argc, char *argv[])
{
    memset(f, 0x3f, sizeof(f));
    int oN;
    cin >> oN;
    const int N = oN * 2;
    for (int i = 1; i <= oN; ++i) {
        cin >> A[i];
        A[i + oN] = A[i];
    }
    for (int i = 1; i <= N; ++i)
        pre[i] = pre[i - 1] + A[i];
    for (int i = 1; i <= N; ++i)
        f[i][i] = 0;
    for (int k = 1; k < oN; ++k) {
        for (int i = 1; i + k <= N; ++i) {
            const int j = i + k;
            for (int s = i; s < j; ++s)
                f[i][j] = min(f[i][j], f[i][s] + f[s + 1][j] + pre[j] - pre[i - 1]),
                    g[i][j] = max(g[i][j], g[i][s] + g[s + 1][j] + pre[j] - pre[i - 1]);
        }
    }
    int ans = 0x3f3f3f3f, am = 0;
    for (int i = 1; i <= oN; ++i)
        ans = min(ans, f[i][i + oN - 1]),
            am = max(am, g[i][i + oN - 1]);
    cout << ans << endl << am << endl;
    return 0;
}
