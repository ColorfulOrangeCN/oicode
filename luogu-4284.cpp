#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 500005;
constexpr double eps = 1e-8;
vector<pair<int, double>> verts[maxn];
double f[maxn];
void dfs(int u, int la)
{
    for (auto [v, w] : verts[u]) {
        if (v == la)
            continue;
        dfs(v, u);
        const double elec = f[v] * w;
        f[u] = f[u] + elec - f[u] * elec;
    }
}
void dfs2(int u, int la)
{
    for (auto [v, w] : verts[u]) {
        if (v == la)
            continue;
        const double elec = f[v] * w;
        if (1 - elec > eps) {
            const double fdu = (f[u] - elec) / (1 - elec) * w;
            f[v] = f[v] + fdu - fdu * f[v];
        }
        dfs2(v, u);
    }
}
int main(int argc, char *argv[])
{
    int N;
    cin >> N;
    for (int i = 1; i < N; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        verts[a].push_back(make_pair(b, w / 100.0));
        verts[b].push_back(make_pair(a, w / 100.0));
    }
    for (int i = 1; i <= N; ++i) {
        cin >> f[i];
        f[i] /= 100;
    }
    dfs(1, 0);
    dfs2(1, 0);
    double ans = 0;
    for (int i = 1; i <= N; ++i)
        ans += f[i];
    printf("%.6lf\n", ans);
    return 0;
}
