#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 3e5 + 1;
constexpr int inf = 0x3f3f3f3f;
int f[maxn], g[maxn], d[maxn];
int N, M;
vector<int> verts[maxn];

void dfs(int u, int la, int len, int& ans) {
    f[u] = -inf;
    g[u] = inf;
    for (int v : verts[u]) {
        if (v == la)
            continue;
        dfs(v, u, len, ans);
        f[u] = max(f[u], f[v] + 1);
        g[u] = min(g[u], g[v] + 1);
    }
    if (g[u] + f[u] <= len)
        f[u] = -inf;
    if (d[u] && g[u] > len)
        f[u] = max(f[u], 0);
    if (f[u] == len) {
        g[u] = 0;
        f[u] = -inf;
        ++ans;
    }    
}
inline bool check(int mid)
{
    int ans = 0;
    dfs(1, 0, mid, ans);
    if (f[1] >= 0)
        ++ans;
    return ans <= M;
}

int main(int argc, char *argv[])
{
    cin >> N >> M;
    copy_n(istream_iterator<int>(cin), N, d + 1);
    for (int i = 1; i < N; ++i) {
        int a, b;
        cin >> a >> b;
        verts[a].push_back(b);
        verts[b].push_back(a);
    }
    int L = 0, R = N, res = N;
    while (L <= R) {
        const int mid = (L + R) / 2;
        if (check(mid)) {
            R = mid - 1;
            res = mid;
        } else {
            L = mid + 1;
        }
    }
    cout << res << endl;
    return 0;
}

