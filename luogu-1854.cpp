#include <bits/stdc++.h>
using namespace std;
const static int maxn = 101;
int f[maxn][maxn] = {0};
int V[maxn][maxn] = {0};

int main(int argc, char *argv[])
{
    memset(f, -0x3f, sizeof(f));
    int N, M;
    cin >> N >> M;
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= M; ++j)
            cin >> V[i][j];
    for (int i = 0; i <= M; ++i)
        f[0][i] = 0;
    for (int i = 1; i <= N; ++i) {
        for (int j = i; j <= M; ++j) {
            f[i][j] = max(f[i - 1][j - 1] + V[i][j], f[i][j - 1]);
        }
    }
    int ans = *max_element(f[N], f[N] + M + 1);
    cout << ans << endl;
    static int ansv[maxn], tp = 0;
    for (int i = N; i; --i) {
        for (int j = i; j <= M; ++j) {
            if (f[i][j] == ans) {
                ans -= V[i][j];
                ansv[tp++] = j;
                break;
            }
        }
    }
    reverse(ansv, ansv + tp);
    copy(ansv, ansv + tp, ostream_iterator<int>(cout, " "));
    cout << endl;
    return 0;
}
