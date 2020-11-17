#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 2.5e5 + 1, mlg = 20, inf = 0x3f3f3f3f;
typedef long long inte;
constexpr inte einf = 0x3f3f3f3f3f3f3f3f;
vector<pair<int, int>> org[maxn], curt[maxn];
int dfn[maxn], f[maxn][mlg], g[maxn][mlg], clk = 0, dep[maxn];
void predfs(int u) {
    dfn[u] = ++clk;
    for (int i = 1; i < mlg; ++i) {
        f[u][i] = f[f[u][i - 1]][i - 1];
        g[u][i] = min(g[u][i - 1], g[f[u][i - 1]][i - 1]);
    }
    for (auto [v, w] : org[u]) {
        if (v == f[u][0])
            continue;
        f[v][0] = u;
        g[v][0] = w;
        dep[v] = dep[u] + 1;
        predfs(v);
    }
}
inline int getPar(int x, int y)
{
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = mlg - 1; i >= 0; --i)
        if (dep[f[x][i]] >= dep[y])
            x = f[x][i];
    if (x == y)
        return x;
    for (int i = mlg - 1; i >= 0; --i)
        if (f[x][i] != f[y][i])
            x = f[x][i], y = f[y][i];
    return f[x][0];
}
inline int colw(int x, int tar)
{
    int ans = inf;
    for (int i = mlg - 1; i >= 0; --i)
        if (dep[f[x][i]] >= dep[tar])
            ans = min(ans, g[x][i]), x = f[x][i];
    return ans;
}
inte dpf[maxn];
bool iskey[maxn];
void dp(int u) {
    dpf[u] = (iskey[u] ? einf : 0);
    for (auto [v, w] : curt[u]) {
        dp(v);
        dpf[u] += min((inte)w, dpf[v]);
    }
    iskey[u] = false;
    curt[u].clear();
}
vector<int> key;
inline void genvt()
{
    sort(begin(key), end(key), [&](int x, int y){return dfn[x] < dfn[y];});
    static int st[maxn], top;
    st[top = 1] = 1;
    assert(curt[1].size() == 0);
    auto ae =
        [&] (int l, int r) -> void {
            // cerr << "Add Edge from " << l << " to " << r << ' ' << colw(r, l) << endl;
            curt[l].push_back(make_pair(r, colw(r, l)));
        };
    for (int u : key) {
        if (u == 1)
            continue;
        iskey[u] = true;
        int lca = getPar(u, st[top]);
        if (lca == st[top]) {
            st[++top] = u;
        } else {
            while (dfn[st[top - 1]] > dfn[lca]) {
                ae(st[top - 1], st[top]);
                --top;
                lca = getPar(u, st[top]);
            }
            if (dfn[lca] > dfn[st[top - 1]])
                ae(lca, st[top]), st[top] = lca;
            else
                ae(lca, st[top--]);
            st[++top] = u;
        }
    }
    while (top > 1) {
        ae(st[top - 1], st[top]);
        --top;
    }
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    memset(g, 0x3f, sizeof(g));
    int N;
    cin >> N;
    for (int i = 1; i < N; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        org[a].push_back(make_pair(b, w));
        org[b].push_back(make_pair(a, w));
    }
    dep[1] = 1;
    predfs(1);
    // copy(dep + 1, dep + N + 1, ostream_iterator<int>(cout, " "));
    int M;
    cin >> M;
    for (int i = 1; i <= M; ++i) {
        int k;
        cin >> k;
        key.resize(k);
        copy_n(istream_iterator<int>(cin), k, key.begin());
        genvt();
        dp(1);
        cout << dpf[1] << endl;
    }
    return 0;
}
