#include <bits/stdc++.h>
using namespace std;

int f[20][20] = {{}};

int dir[20][20] = {{}};
int used[20];
int main(int argc, char *argv[])
{
    int N, M;
    cin >> N >> M;
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= M; ++j)
            cin >> dir[i][j];
    for (int i = N; i; --i) {
        for (int j = 0; j <= M; ++j) {
            for (int k = 0; k <= j; ++k) {
                f[i][j] = max(f[i][j], f[i + 1][j - k] + dir[i][k]);
            }
        }
    }
    int ans = f[1][M], suf = M;
    cout << ans << endl;
    for (int i = 1; i <= N; ++i) {
        for (int j = suf; j >= 0; --j) {
            if (f[i][suf] == f[i + 1][j] + dir[i][suf - j]) {
                used[i] = suf - j;
                cout << i << ' ' << suf - j << endl;
                suf = j;
                break;
            }
        }
    }
    return 0;
}
