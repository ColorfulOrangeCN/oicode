#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e5 + 1, lgn = 20, sqn = 300;
vector<int> verts[maxn];
int in[maxn], out[maxn];
struct Que {
    int l, r, lca;
    int id;
} qs[maxn];
bool operator < (Que a, Que b) {return (a.l / sqn == b.l / sqn ? ((a.l / sqn) & 1 ? a.r < b.r : a.r > b.r) : a.l < b.l);}
int ids[maxn * 2];
int clk = 0;
int dep[maxn];
int f[maxn][lgn];
void dfs(int u) {
    ++clk;
    ids[in[u] = clk] = u;
    dep[u] = dep[f[u][0]] + 1;
    for (int i = 1; i < lgn && f[u][i - 1]; ++i)
        f[u][i] = f[f[u][i - 1]][i - 1];
    for (int v : verts[u]) {
        if (in[v])
            continue;
        f[v][0] = u;
        dfs(v);
    }
    ++clk;
    ids[out[u] = clk] = u;
}
inline int getLCA(int x, int y) {
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = lgn - 1; i >= 0; --i)
        if (dep[f[x][i]] >= dep[y])
            x = f[x][i];
    if (x == y)
        return x;
    for (int i = lgn - 1; i >= 0; --i)
        if (f[x][i] != f[y][i])
            x = f[x][i], y = f[y][i];
    return f[x][0];
}

inline bool belong(int x, int y) {
    return (in[x] <= in[y] && in[y] <= out[x]);
}
int col[maxn], plc[maxn];
bool vis[maxn];
int cnt = 0, times[maxn] = {0};
int num = 0;
inline void cc(int x, int v) {
    // assert(x < 8);
    times[x] += v;
    if (times[x] == 0 && v == -1)
        --cnt;
    else if (times[x] == 1 && v == 1)
        ++cnt;
    num += v;
}
inline void modify(int x) {
    cc(col[ids[x]], (vis[ids[x]] ? -1 : 1));
    vis[ids[x]] ^= 1;
}
int ans[maxn];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, M;
    cin >> N >> M;
    copy_n(istream_iterator<int>(cin), N, col + 1);
    copy(col + 1, col + N + 1, plc);
    sort(plc, plc + N);
    transform(col + 1, col + N + 1, col + 1, [&](int x) {return lower_bound(plc, plc + N, x) - plc;});
    for (int i = 1; i < N; ++i) {
        int a, b;
        cin >> a >> b;
        verts[a].push_back(b);
        verts[b].push_back(a);
    }
    dfs(1);
    // copy(ids + 1, ids + clk + 1, ostream_iterator<int> (cerr, " "));
    // cerr << endl;
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        if (in[u] > in[v])
            swap(u, v);
        const int lca = getLCA(u, v);
        // cerr << lca << endl;
        qs[i] = Que{lca == u ? in[u] : out[u], in[v], lca == u ? 0 : lca, i};
        // copy(ids + qs[i].l, ids + qs[i].r + 1, ostream_iterator<int>(cout, " "));
        // cout << endl;
    }
    sort(qs, qs + M);
    int L = 1, R = 1;
    for (int i = 0; i < M; ++i) {
        // cerr << qs[i].l << ' ' << qs[i].r << endl;
        assert(qs[i].l <= qs[i].r);
        while (R <= qs[i].r)
            modify(R++);
        while (L > qs[i].l)
            modify(--L);
        while (L < qs[i].l)
            modify(L++);
        while (R > qs[i].r + 1)
            modify(--R);
        // assert(L == qs[i].l && R == qs[i].r + 1);
        
        if (qs[i].lca)
            modify(in[qs[i].lca]);
        ans[qs[i].id] = cnt;
        if (qs[i].lca)
            modify(in[qs[i].lca]);
        // cerr << "gap" << endl;
    }
    copy(ans, ans + M, ostream_iterator<int>(cout, "\n"));
    return 0;
}
