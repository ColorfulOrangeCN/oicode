#include <bits/stdc++.h>
using namespace std;
const static int maxn = 1e5 + 4;
struct Edge {
    int u, v, w;
} edges[maxn];
list<int> verts[maxn];
typedef typename list<int>::iterator Ep;
inline int getVer(int eid, int u) {return (edges[eid].v == u ? edges[eid].u : edges[eid].v);}
inline void buildEdge(int eid)
{
    verts[edges[eid].u].push_back(eid);
    verts[edges[eid].v].push_back(eid);
}

bool vis[maxn];
int cnt = 0;
void dfs(int u, int la, int t3, int t2)
{
    assert(!vis[u]);
    vis[u] = true;
    ++cnt;
    for (Ep it = verts[u].begin(); it != verts[u].end(); ++it) {
        const int v = getVer(*it, u);
        if (v == la)
            continue;
        if ((t3 && edges[*it].w == 3) || (t2 && edges[*it].w == 3))
            continue;
        dfs(v, u, t3 + (edges[*it].w == 3), t2 + (edges[*it].w == 2));
    }
}
int target;
bool dre(int u, int la) {
    if (u == target)
        return true;
    bool flag = 0;
    for (Ep it = verts[u].begin(); it != verts[u].end(); ++it) {
        const int v = getVer(*it, u);
        if (v == la)
            continue;
        if (dre(v, u)) {
            flag = true;
            edges[*it].w = max(1, edges[*it].w - 1);
        }
    }
    return flag;
}
int N, M;
inline void sf()
{
    for (int i = 1; i < N; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        buildEdge(i);
    }
    for (int i = 1; i <= M; ++i) {
        int a, b, s, t;
        cin >> a >> b >> t >> s;
        target = b;
        dre(a, 0);
        fill(vis, vis + N + 1, false);
        cnt = 0;
        dfs(t, 0, 0, 0);
        cout << vis[s] << ' ' << cnt << endl;
    }
}
inline void ss2()
{
    static int V[maxn];
    int cnt2 = 0, cnt3 = 0;
    V[1] = 1;
    for (int i = 1; i < N; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        if (a != 1)
            swap(a, b);
        V[b] = w;
        if (w == 2)
            ++cnt2;
        else if (w == 3)
            ++cnt3;
    }
    for (int i = 1; i <= M; ++i) {
        int a, b, s, t;
        cin >> a >> b >> t >> s;
        if (V[a] == 3) 
            --cnt3, ++cnt2;
        else if (V[a] == 2)
            --cnt2;
        V[a] = max(1, V[a] - 1);
        if (V[b] == 3) 
            --cnt3, ++cnt2;
        else if (V[b] == 2)
            --cnt2;
        V[b] = max(1, V[b] - 1);
        int ans = 0;
        if (V[t] == 1) {
            cout << "1 " << N << endl;
        } else {
            cout << (V[s] != 3) << ' ' << N - cnt3 + (V[t] == 3) << endl;
        }
    }
}
int main()
{
    freopen("brain.in", "r", stdin);
    freopen("brain.out", "w", stdout);
    cin >> N >> M;
    if (N * M <= 4e6) {
        sf();
    } else {
        ss2();
    }
    return 0;
}