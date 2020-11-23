#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 4e5 + 1;
vector<int> verts[maxn];
int size[maxn], f[maxn][2], g[maxn];
int N;
inline void exc(int u, int v) {
    if (v > f[u][0]) {
        f[u][1] = f[u][0];
        f[u][0] = v;
    } else if (f[u][1] < v){
        f[u][1] = v;
    }
}
void dfs(int u, int la) {
    size[u] = 1;
    for (int v : verts[u]) {
        if (v == la)
            continue;
        dfs(v, u);
        size[u] += size[v];
        int x = f[v][0];
        if (size[v] <= N / 2)
            x = max(x, size[v]);
        exc(u, x);
    }
}
bool able[maxn];
void getans(int u, int la) {
    int c = 0;
    if (N - size[u] > N / 2) {
        if (N - size[u] - g[u] <= N / 2)
            ++c;
        else
            c = 100;
    }
    for (int v : verts[u]) {
        if (v == la)
            continue;
        g[v] = max(g[u], g[v]);
        g[v] = max(g[v], (N - size[u] <= N / 2 ? N - size[u] : 0));
        if (f[v][0] == f[u][0] || size[v] == f[u][0])
            g[v] = max({g[v], f[u][1]});
        else
            g[v] = max({g[v], f[u][0]});
        if (size[v] > N / 2) {
            if (size[v] - f[v][0] <= N / 2)
                ++c;
            else
                c = 100;
        }
        getans(v, u);
    }
    // cerr << u << ' ' << c << ' ' << g[u] << ' ' << f[u][0] << ' ' << size[u]<< ' ' << endl;
    if (c <= 1)
        able[u] = true;
}
int main() {
    cin >> N;
    for (int i = 1; i < N; ++i) {
        int a, b;
        cin >> a >> b;
        verts[a].push_back(b);
        verts[b].push_back(a);
    }
    dfs(1, 0);
    size[0] = size[1];
    getans(1, 0);
    copy(able + 1, able + N + 1, ostream_iterator<bool>(cout, " "));
    return 0;
}
