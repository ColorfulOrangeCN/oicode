#include <bits/stdc++.h>
using namespace std;
const static int maxn = 1002;
char pic[maxn][maxn] = {};
int dis[maxn][maxn];
bool vis[maxn][maxn] = {};
int dx[maxn] = {0, 0, 1, -1}, dy[maxn] = {1, -1, 0, 0};
typedef pair<int, int> Point;
int main(int argc, char *argv[])
{
    int N, M, T;
    cin >> N >> M >> T;
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= M; ++j)
            cin >> pic[i][j];
    queue<Point> q;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            bool flag = false;
            for (int k = 0; k < 4; ++k) {
                if (pic[i + dx[k]][j + dy[k]] == pic[i][j]) {
                    flag = true;
                    break;
                }
            }
            if (flag) {
                q.push(make_pair(i, j));
                vis[i][j] = true;
                dis[i][j] = 0;
            }
        }
    }
    while (!q.empty()) {
        const int x = q.front().first, y = q.front().second;
        q.pop();
        for (int k = 0; k < 4; ++k) {
            const int nx = x + dx[k], ny = y + dy[k];
            if (pic[nx][ny] && !vis[nx][ny]) {
                dis[nx][ny] = dis[x][y] + 1;
                vis[nx][ny] = true;
                q.push(make_pair(nx, ny));
            }
        }
    }
    for (int i = 0; i < T; ++i) {
        long long p, x, y;
        cin >> x >> y >> p;
        if (p < dis[x][y] || !vis[x][y]) {
            cout << pic[x][y] << endl;
        } else {
            const long long k = (p - dis[x][y]) & 1;
            if (k)
                cout << (pic[x][y] == '0' ? '1' : '0') << endl;
            else
                cout << pic[x][y] << endl;
        }
    }
    return 0;
}
