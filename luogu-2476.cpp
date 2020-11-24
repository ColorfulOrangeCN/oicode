#include <bits/stdc++.h>
using namespace std;
constexpr int maxk = 16, maxc = 5;
typedef long long inte;
constexpr inte mods = 1e9 + 7;
inte f[maxk][maxk][maxk][maxk][maxk][maxc];
bool vis[maxk][maxk][maxk][maxk][maxk][maxc];
int cc[maxk];
inte solve(int a, int b, int c, int d, int e, int k) {
    inte res = 0;
    if (a + b + c + d + e == 0)
        return 1;
    if (vis[a][b][c][d][e][k])
        return f[a][b][c][d][e][k];
    if (a)
        res += (a - (k == 2)) * solve(a - 1, b, c, d, e, 1);
    if (b)
        res += (b - (k == 3)) * solve(a + 1, b - 1, c, d, e, 2);
    if (c)
        res += (c - (k == 4)) * solve(a, b + 1, c - 1, d, e, 3);
    if (d)
        res += (d - (k == 5)) * solve(a, b, c + 1, d - 1, e, 4);
    if (e)
        res += e * solve(a, b, c, d + 1, e - 1, 5);
    vis[a][b][c][d][e][k] = true;
    return f[a][b][c][d][e][k] = res % mods;
}
int main() {
    int K;
    cin >> K;
    for (int i = 1; i <= K; ++i) {
        int c;
        cin >> c;
        ++cc[c];
    }
    cout << solve(cc[1], cc[2], cc[3], cc[4], cc[5], 0);
    return 0;
}
