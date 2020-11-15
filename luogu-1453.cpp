#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 1;
typedef long long inte;
const static inte inf = 0x3f3f3f3f;

struct Edge {
    int v, nxt;
} edges[maxn * 2 + 2];
int head[maxn] = {0};
inline void addEdge(int u, int v)
{
    static int newp = 1;
    edges[++newp].v = v;
    edges[newp].nxt = head[u];
    head[u] = newp;
}

int V[maxn];

bool ins[maxn] = {0};
bool vis[maxn] = {0};
int tag = 0, src, des;
void findcir(int u, int la)
{
    vis[u] = true;
    ins[u] = true;
    for (int i = head[u]; i; i = edges[i].nxt) {
        const int v = edges[i].v;
        if ((i ^ 1) == la)
            continue;
        if (ins[v]) {
            tag = i;
            src = u, des = v;
            break;
        }
        findcir(v, i);
    }
    ins[u] = false;
}

inte f[maxn][2];

void dfs(int u, int la)
{
    f[u][1] = V[u];
    f[u][0] = 0;
    for (int i = head[u]; i; i = edges[i].nxt) {
        const int v = edges[i].v;
        if ((i ^ 1) == la || i == tag || i == (tag ^ 1))
            continue;
        dfs(v, i);
        f[u][1] += f[v][0];
        f[u][0] += max(f[v][0], f[v][1]);
    }
}

int main()
{
    int N;
    cin >> N;
    for (int i = 1; i <= N; ++i)
        cin >> V[i];
    for (int i = 1; i <= N; ++i) {
        int a, b;
        cin >> a >> b;
        ++a, ++b;
        addEdge(b, a);
        addEdge(a, b);
    }
    inte ra = 0;
    for (int i = 1; i <= N; ++i) {
        if (vis[i])
            continue;
        tag = 0;
        findcir(i, 0);
        inte ans = 0;
        dfs(src, 0);
        ans = max(ans, f[src][0]);
        dfs(des, 0);
        ans = max(ans, f[des][0]);
        ra += ans;
    }
    double k;
    scanf("%lf", &k);
    printf("%.1lf\n", k * ra);
    return 0;
}
