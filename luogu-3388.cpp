#include <bits/stdc++.h>
using namespace std;
const static int maxm = 1e5 + 1, maxn = 2e4 + 1;
struct Edge
{
    int v, nxt; 
} edges[maxm * 2];
int head[maxn], newp = 0;
void addEdge(int u, int v)
{
    edges[++newp].v = v;
    edges[newp].nxt = head[u];
    head[u] = newp;
}

int st[maxn], stp = 0;
int cutp[maxn], ccp = 0;
#define letmin(l, r) ((l) > (r) ? ((l) = (r)) : (l))
int dfn[maxn] = {0}, low[maxn] = {0};
int clk = 0;
void dfs(int u, int la)
{
    
    dfn[u] = low[u] = ++clk;
    int ch = 0;
    bool isc = false;
    for (int i = head[u]; i; i = edges[i].nxt) {
        const int v = edges[i].v;
        if (v == la)
            continue;
        if (!dfn[v]) {
            dfs(v, u);
            ++ch;
            letmin(low[u], low[v]);
            if (la && dfn[u] <= low[v])
                isc = true; 
        } else {
            letmin(low[u], dfn[v]);
        }
    }
    if (la == 0) {
        if (ch > 1)
            cutp[ccp++] = u;
    } else if(isc) {
        cutp[ccp++] = u;
    }
}

signed main()
{
    int N, M;
    cin >> N >> M;
    for (int i = 1; i <= M; ++i) {
        int a,b;
        cin >> a >> b;
        addEdge(a, b);
        addEdge(b, a);
    }
    for (int i = 1; i <= N; ++i) {
        if (dfn[i] == 0)
            dfs(i, 0);
    }
    cout << ccp << endl;
    sort(cutp, cutp + ccp);
    copy(cutp, cutp + ccp, ostream_iterator<int>(cout, " "));
    return 0;
}

