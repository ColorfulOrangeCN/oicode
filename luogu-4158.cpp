#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 51, base = 10;
int N, M;
struct DP {
    int v, c;
} f[maxn][maxn][3];
inline bool operator < (const DP& a, const DP& b) {return a.v < b.v;}
inline DP operator + (const DP& a, const DP& b) {return DP{a.v + b.v, a.c + b.c};}
int sufr[maxn][maxn];
char board[maxn][maxn];
DP ans;
void run(int extrav)
{
    ans = DP{0, 0};
    for (int i = 1; i <= N; ++i) {
        f[i][1][0] = DP{0, 0};
        f[i][1][1] = DP{base - extrav, 1};
        f[i][1][2] = DP{-extrav, 1};
        for (int j = 2; j <= M; ++j) {
            f[i][j][0] = max({f[i][j - 1][0], f[i][j - 1][1], f[i][j - 1][2]});
            if (board[i][j] == board[i][j - 1]) {
                f[i][j][1] = max(f[i][j - 1][1] + DP{base, 0}, max(f[i][j - 1][0], f[i][j - 1][2]) + DP{base - extrav, 1});
                f[i][j][2] = max(f[i][j - 1][2], max(f[i][j - 1][0], f[i][j - 1][1]) + DP{-extrav, 1});
            } else {
                f[i][j][1] = max(f[i][j - 1][2] + DP{base, 0}, max(f[i][j - 1][0], f[i][j - 1][1]) + DP{base - extrav, 1});
                f[i][j][2] = max(f[i][j - 1][1], max(f[i][j - 1][0], f[i][j - 1][2]) + DP{-extrav, 1});
            }
        }
        ans = ans + max({f[i][M][0], f[i][M][1], f[i][M][2]});
    }
}
int main(int argc, char *argv[])
{
    int T;
    cin >> N >> M >> T;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            cin >> board[i][j];
            sufr[i][j] = sufr[i][j - 1] + (board[i][j] == 1);
        }
    }
    int L = 0, R = M * base, res = 0;
    while (L <= R) {
        const int mid = (L + R) / 2;
        run(mid);
        if (ans.c <= T) {
            R = mid - 1;
            res = mid;
        } else {
            L = mid + 1;
        }
    }
    run(res);
    cout << (ans.v + res * T) / base << endl;
    return 0;
}
