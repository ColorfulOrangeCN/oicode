#include <bits/stdc++.h>
using namespace std;

const int maxn = 101, maxm = 21, inf = 0x3f3f3f3f;
typedef long long inte;

int edges[maxm][maxm];

int N, M, K, E, D;
bool vis[maxm];

template<typename T>
inline T& letmin(T& l, const T& r)
{
    return (l > r ? l = r : l);
}

int diji() {
    static int dis[maxn];
    memset(dis, inf, sizeof(dis));
    dis[1] = 0;
    for (int i = 1; i < M; ++i) {
        int u = M;
        for (int j = 1; j <= M; ++j)
            if (dis[j] < dis[u] && !vis[j])
                u = j;
        vis[u] = true;
        for (int v = 1; v <= M; ++v)
            letmin(dis[v], dis[u] + edges[u][v]);
    }
    return dis[M];
}

int f[maxn];

struct Limit
{
    int l, r, p;
} lims[100001];

int main(int argc, char *argv[])
{
    cin >> N >> M >> K >> E;
    memset(edges, inf, sizeof(edges));
    for (int i = 1; i <= E; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        letmin(edges[a][b], c);
        letmin(edges[b][a], c);
    }
    for (int i = 1; i <= M; ++i)
        letmin(edges[i][i], 0);
    cin >> D;
    for (int i = 1; i <= D; ++i)
        cin >> lims[i].p >> lims[i].l >> lims[i].r;
    memset(f, inf, sizeof(f));
    f[0] = 0;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            memset(vis, 0, sizeof(vis));
            for (int p = 1; p <= D; ++p) {
                if (lims[p].l <= i && lims[p].r >= j)
                    vis[lims[p].p] = true;
            }
            int d = diji();
            if (d < inf)
                letmin(f[i], f[j - 1] + d * (i - j + 1) + K);
        }
    }
    cout << f[N] - K << endl;
    return 0;
}
