#include <bits/stdc++.h>
using namespace std;
const static int maxn = 1e5 + 1;
vector<int> verts[maxn];

int dep[maxn] = {0};
bool vis[2] = {false, false};

int ans;

void dfs(int u, int la)
{
    bool cnt = 0;
    for (int v : verts[u]) {
        if (v == la)
            continue;
        dep[v] = dep[u] + 1;
        if (verts[v].size() == 1) {
            --ans, cnt = true;
            vis[dep[v] % 2] = true;
        }
        dfs(v, u);
    }
    ans += cnt;
}

int main(int argc, char *argv[])
{
    int N;
    cin >> N;
    ans = N - 1;
    for (int i = 1; i < N; ++i) {
        int a, b;
        cin >> a >> b;
        verts[a].push_back(b);
        verts[b].push_back(a);
    }
    for (int i = 1; i <= N; ++i) {
        if (verts[i].size() > 1) {
            dfs(i, 0);
            break;
        }
    }
    cout << 1 + 2 * (vis[0] && vis[1]) << ' ' << ans << endl;
    return 0;
}
