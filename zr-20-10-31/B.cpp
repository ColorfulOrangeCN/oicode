#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e5 + 1;

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

int ans = 0;
int col[maxn];

int dfs1(int u, int la)
{
    int f = 0, g = 0;
    for (int i = head[u]; i; i = edges[i].nxt) {
        const int v = edges[i].v;
        if (v == la)
            continue;
        ;
        int t = dfs1(v, u) + (col[u] != col[v]);
        if (t > f)
            swap(f, g), f = t;
        else if (t > g)
            g = t;
    }
    ans = max(ans, f + g);
    return f;
}

int main(int argc, char *argv[])
{
    int N;
    cin >> N;
    for (int i = 1; i <= N; ++i)
        cin >> col[i];
    for (int i = 1; i < N; ++i) {
        int a,b;
        cin >> a >> b;
        addEdge(a, b);
        addEdge(b, a);
    }
    dfs1(1, 0);
    cout << (ans + 1) / 2 << endl;
    return 0;
}
