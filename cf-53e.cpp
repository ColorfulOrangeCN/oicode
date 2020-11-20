#include <bits/stdc++.h>
using namespace std;
inline int lowbit(int x) {return x & (-x);}
constexpr int maxn = 10, maxst = (1 << maxn);
int f[maxst][maxst];
int g[maxn][maxn];
inline int getbit(int x) {return (1 << (x - 1));}
int main(int argc, char *argv[])
{
    int N, M, K;
    cin >> N >> M >> K;
    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        ++g[a][b];
        ++g[b][a];
    }
    const int mst = (1 << N);
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j)
                f[getbit(i) | getbit(j)][getbit(i) | getbit(j)] = g[i][j];
    for (int s = 1; s < mst; ++s) {
        for (int t = s; t; (--t) &= s) {
            for (int i = 1; i <= N; ++i) {
                if (getbit(i) & s) {
                    for (int j = 1; j <= N; ++j) {
                        if ((getbit(j) & ~s) && (!(((t & ~getbit(i)) | getbit(j)) >> j)))
                            f[s | getbit(j)][t ^ getbit(j) ^ (getbit(i) & t ? getbit(i) : 0)] += f[s][t] * g[i][j];
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int s = 1; s < mst; ++s) {
        if (__builtin_popcount(s) == K)
            ans += f[mst - 1][s];
    }
    cout << ans << endl;
    return 0;
}
