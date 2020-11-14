#include <bits/stdc++.h>
using namespace std;
const static int maxm = 5e5 + 1, maxn = 1e5 + 1;
struct Edge {
    int u, v;
} edges[maxm];
bool vis[maxn];
int taged[maxn], tc = 0;
int added[maxn], ac = 0;
vector<int> verts[maxn];
void dfs(int u)
{
    if (vis[u])
        return;
    vis[u] = true;
    taged[tc++] = u;
    for (int i = 0; i < verts[u].size(); ++i) {
        const int v = verts[u][i];
        dfs(v);
    }
}
inline void pushe(int eid)
{
    const int u = edges[eid].u, v = edges[eid].v;   
    added[ac++] = u;
    verts[u].push_back(v);
    if (vis[u])
        dfs(v);
}
inline void reset()
{
    for (int i = 0; i < tc; ++i)
        vis[taged[i]] = false;
    tc = 0;
    for (int i = 0; i < ac; ++i)
        verts[added[i]].clear();
    ac = 0;
    vis[1] = true;
}
int main()
{
    freopen("graph.in", "r", stdin);
    freopen("graph.out", "w", stdout);
    int N, M;
    cin >> N >> M;
    for (int i = 1; i <= M; ++i)
        cin >> edges[i].u >> edges[i].v;
    int la, ans = 1;
    vis[1] = true;
    for (int i = 1; i <= M; ++i) {
        pushe(i);
        if (vis[N]) {
            ++ans;
            reset();
            pushe(i);
        }
    }
    cout << ans << endl;
    return 0;
}