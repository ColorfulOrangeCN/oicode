#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 205, maxnd = maxn * maxn, inf = 0x3f3f3f3f;
constexpr int dx[] = {1, 1, -1, -1, 2, 2, -2, -2}, dy[] = {2, -2, 2, -2, 1, -1, 1, -1};
struct Edge {
    int v, nxt, w;
} edges[maxnd * 6 * 8];
int newp = 1;
int head[maxnd] = {0}, cur[maxnd];
inline void addEdge(int u, int v, int w) {
    edges[++newp].v = v;
    edges[newp].w = w;
    edges[newp].nxt = head[u];
    head[u] = newp;
}
inline void addFlow(int u, int v, int w) {
    addEdge(u, v, w);
    addEdge(v, u, 0);
}
int N, M;
inline int getid(int x, int y) {return N * (x - 1) + y + 1;}
bool vis[maxn][maxn];
int dep[maxnd];
inline bool bfs()
{
    memset(dep, 0, sizeof(dep));
    queue<int> q;
    q.push(1);
    dep[1] = 1;
    memcpy(cur, head, sizeof(head));
    while (!q.empty()) {
        const int u = q.front();
        q.pop();
        for (int i = head[u]; i; i = edges[i].nxt) {
            const int v = edges[i].v, w = edges[i].w;
            if (!w || dep[v])
                continue;
            dep[v] = dep[u] + 1;
            q.push(v);
        }
    }
    return dep[getid(N, N) + 1];
}
int dfs(int u, int delta)
{
    if (u == getid(N, N) + 1)
        return delta;
    int cf = 0;
    for (int &i = cur[u]; i && delta; i = edges[i].nxt) {
        const int v = edges[i].v, w = edges[i].w;
        if (!w || dep[v] != dep[u] + 1)
            continue;
        int f = dfs(v, min(delta, w));
        edges[i].w -= f;
        edges[i ^ 1].w += f;
        cf += f;
        delta -= f;
    }
    return cf;
}
int main(int argc, char *argv[])
{
    cin >> N;
    int M = 0;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            char c;
            cin >> c;
            M += (vis[i][j] = (c == '1'));
        }
    }
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            if (!vis[i][j]) {
                if ((i + j) & 1) {
                    addFlow(1, getid(i, j), 1);
                    for (int k = 0; k < 8; ++k) {
                        const int x = i + dx[k], y = j + dy[k];
                        if (x > 0 && x <= N && y > 0 && y <= N)
                            addFlow(getid(i, j), getid(x, y), inf);
                    }
                } else {
                    addFlow(getid(i, j), getid(N, N) + 1, 1);
                }
            }
        }
    }
    int ans = 0;
    // cerr << bfs() << endl;
    while (bfs())
        ans += dfs(1, inf);
    cout << N * N - M - ans << endl;
    return 0;
}
