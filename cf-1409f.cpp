#include <bits/stdc++.h>
using namespace std;

const static int maxn = 201;
int f[maxn][maxn][maxn] = {{{0}}};
int N, K;
int main(int argc, char *argv[])
{
    cin >> N >> K;
    string str;
    char t[4];
    cin >> str >> t;
    assert(N == str.length());
    assert(strlen(t) == 2);
    memset(f, -0x3f, sizeof(f));
    f[0][0][0] = 0;
    if (t[0] == t[1]) {
        int cnt = 0;
        for (int i = 0; i < N; ++i)
            cnt += (str[i] == t[0]);
        const int v = min(cnt + K, N);
        cout << v * (v - 1) / 2 << endl;
        return 0;
    }
    for (int i = 1; i <= N; ++i) {
        const char c = str[i - 1];
        for (int j = 0; j <= i; ++j) {
            for (int k = 0; k <= K; ++k) {
                if (!(c == t[0] && j == 0))f[i][j][k] = (c == t[0] ? f[i - 1][j - 1][k] : (c == t[1] ? f[i - 1][j][k] + j : f[i - 1][j][k]));
                if (!k)
                    continue;
                f[i][j][k] = max(f[i][j][k],  f[i - 1][j][k - 1] + j);
                if (j != 0) f[i][j][k] = max(f[i][j][k], f[i - 1][j - 1][k - 1]);
            }
        }
    }
    int ans = 0;
    for (int j = 0; j <= N; ++j) {
        for (int k = 0; k <= K; ++k)
            ans = max(ans, f[N][j][k]);
    }
    cout << ans << endl;
    return 0;
}
