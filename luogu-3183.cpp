#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 1;
struct Edge {
    int v, nxt;
} edges[maxn * 2];
int head[maxn] = {0}, in[maxn], out[maxn];
inline void addEdge(int u, int v)
{
    static int newp = 0;
    edges[++newp].v = v;
    edges[newp].nxt = head[u];
    head[u] = newp;
    ++in[v];
    ++out[u];
}

typedef long long inte;

int dp[maxn] = {0};

inte dfs(int u)
{
    int acm = 0;
    if (dp[u])
        return dp[u];
    if (in[u] && !out[u])
        ++acm;
    for (int i = head[u]; i; i = edges[i].nxt) {
        const int v = edges[i].v;
        acm += dfs(v);
    }
    return dp[u] = acm;
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, M;
    cin >> N >> M;
    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        addEdge(a, b);
    }
    int ans = 0;
    for (int i = 1; i <= N; ++i) {
        if (!in[i])
            ans += dfs(i);
    }
    cout << ans << endl;
    return 0;
}
