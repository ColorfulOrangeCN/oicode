#include <bits/stdc++.h>
using namespace std;
const static int maxn = 31;
int main(int argc, char *argv[])
{
    int M, N;
    static int po[maxn][maxn];
    typedef long long inte;
    static bool vis[maxn][maxn];
    typedef tuple<int, int, int, int> Point;
    // io
    cin >> N >> M;
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= M; ++j)
            cin >> po[i][j];
    priority_queue<Point, vector<Point>, greater<Point>> q;
    static int used[maxn][maxn], dis[maxn][maxn];
    static inte cnt[maxn][maxn];
    while (!q.empty()) {
        auto [u, d, x, y] = q.top();
        if (vis[x][y])
            continue;
        vis[x][y] = true;
        constexpr int dir = 8, dx[dir] = {1, 1, 2, 2, -1, -1, -2, -2}, dy[dir] = {2, -2, 1, -1, 2, -1, 1, -1};
        for (int k = 0; k < dir; ++k) {
            const int nx = x + dx[k], ny = y + dy[k];
            // TODO
        }
    }
    return 0;
}
