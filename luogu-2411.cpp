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
    cin >> N >> M;
    auto forg =
        [&](auto f) {
            for (int i = 1; i <= N; ++i)
                for (int j = 1; j <= M; ++j)
                    f(i, j);
        };
    forg([&](int i, int j){cin >> po[i][j];});
    auto check = [N, M](int x, int y) {return x <= N && x >= 1 && y <= M && y >= 1;};
    priority_queue<Point, vector<Point>, greater<Point>> q;
    static int used[maxn][maxn], dis[maxn][maxn];
    static inte cnt[maxn][maxn];
    memset(used, 0x3f, sizeof(used));
    memset(dis, 0x3f, sizeof(dis));
    forg([&](int i, int j) {
             if (po[i][j] == 3) {
                 q.push(Point(0, 0, i, j));
                 tie(used[i][j], dis[i][j], cnt[i][j]) = make_tuple(0, 0, 1);
             }
         });
    while (!q.empty()) {
        auto [u, d, x, y] = q.top();
        q.pop();
        if (vis[x][y])
            continue;
        vis[x][y] = true;
        constexpr int dir = 8, dx[dir] = {1, 1, 2, 2, -1, -1, -2, -2}, dy[dir] = {2, -2, 1, -1, 2, -2, 1, -1};
        for (int k = 0; k < dir; ++k) {
            const int nx = x + dx[k], ny = y + dy[k];
            if (!check(nx, ny) || po[nx][ny] == 2)
                continue;
            Point p;
            if (po[nx][ny] == 0)
                p = (Point(u + 1, d + 1, nx, ny));
            else
                p = (Point(u, d + 1, nx, ny));
            const tuple<int, int> cur(get<0>(p), get<1>(p)), st(used[nx][ny], dis[nx][ny]);
            if (cur < st)
                tie(used[nx][ny], dis[nx][ny]) = cur, cnt[nx][ny] = cnt[x][y], q.push(p);
            else if (cur == st)
                cnt[nx][ny] += cnt[x][y];
        }
    }
    pair<int, int> ansp;
    forg([&](int i, int j) { if (po[i][j] == 4) ansp = make_pair(i, j); });
    if (!vis[ansp.first][ansp.second])
        cout << -1 << endl;
    else
        cout << used[ansp.first][ansp.second] << endl << dis[ansp.first][ansp.second] << endl << cnt[ansp.first][ansp.second];
    return 0;
}
