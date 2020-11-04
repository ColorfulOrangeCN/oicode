#include <bits/stdc++.h>
using namespace std;

const static int maxn = 1e5 + 1, lgn = 20;

struct Edge
{
    int v, nxt;
} edges[maxn * 2];
int head[maxn] = {0}, newp = 0;
inline void addEdge(int u, int v)
{
    edges[++newp].v = v;
    edges[newp].nxt = head[u];
    head[u] = newp;
}

int f[maxn][lgn], dep[maxn];

void predfs(int u)
{
    for (int i = 1; i < lgn; ++i)
        f[u][i] = f[f[u][i - 1]][i - 1];
    for (int i = head[u]; i; i = edges[i].nxt) {
        const int v = edges[i].v;
        if (v == f[u][0])
            continue;
        f[v][0] = u;
        dep[v] = dep[u] + 1;
        predfs(v);
    }
}

int adj[maxn];

inline int getCP(int x, int y) {
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = lgn - 1; i >= 0; --i) {
        if (dep[f[x][i]] >= dep[y])
            x = f[x][i];
    }
    if (x == y)
        return x;
    for (int i = lgn - 1; i >= 0; --i) {
        if (f[x][i] != f[y][i]) {
            x = f[x][i];
            y = f[y][i];
        }
    }
    return f[x][0];
}

int ans = 0;

int dfs(int u)
{
    int acm = adj[u];
    for (int i = head[u]; i; i = edges[i].nxt) {
        const int v = edges[i].v;
        if (v == f[u][0])
            continue;
        acm += dfs(v);
    }
    ans = max(ans, acm);
    return acm;
}

int main(int argc, char *argv[])
{
    int N, K;
    cin >> N >> K;
    for (int i = 1; i < N; ++i) {
        int a, b;
        cin >> a >> b;
        addEdge(a, b);
        addEdge(b, a);
    }
    dep[1] = 1;
    predfs(1);
    for (int i = 1; i <= K; ++i) {
        int s, t;
        cin >> s >> t;
        ++adj[s], ++adj[t];
        --adj[getCP(s, t)];
        --adj[f[getCP(s, t)][0]];
    }
    dfs(1);
    cout << ans << endl;
    return 0;
}
