#include <bits/stdc++.h>
using namespace std;
const int maxn = 51, maxcnt = 500;
int f[maxn][maxn][maxcnt] = {};
bool vis[maxn][maxn][maxcnt] = {};
int col[maxn], sz[maxn];
inline int p2(int x) {return x * x;}
int dfs(int l, int r, int lx)
{
    if (l == r)
        return p2(sz[l] + lx);
    if (vis[l][r][lx])
        return f[l][r][lx];
    vis[l][r][lx] = true;
    int res = dfs(l, r - 1, 0) + p2(sz[r] + lx);
    for (int k = l; k < r; ++k)
        if (col[k] == col[r])
            res = max(res, dfs(l, k, sz[r] + lx) + dfs(k + 1, r - 1, 0));
    return f[l][r][lx] = res;
}
int main()
{
    int M;
    cin >> M;
    copy_n(istream_iterator<int>(cin), M, col + 1);
    copy_n(istream_iterator<int>(cin), M, sz + 1);
    cout << dfs(1, M, 0) << endl;
    return 0;
}
