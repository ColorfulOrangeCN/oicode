#include <bits/stdc++.h>
using namespace std;
const static int maxn = 1e5 + 1;
vector<int> verts[maxn];
int dep[maxn];
int midl = 0;
int dfs(int u, int la)
{
    int f1 = 0, f2 = 0;
    for (int v : verts[u]) {
        if (v == la)
            continue;
        dep[v] = dep[u] + 1;
        const int d = dfs(v, u) + 1;
        if (d > f1) {
            f2 = f1;
            f1 = d;
        } else if (d > f2) {
            f2 = d;
        }
    }
    midl = max(midl, f1 + f2);
    return f1;
}

int main(int argc, char *argv[])
{
    int T;
    cin >> T;
    while (T--) {
        int N, a, b, da, db;
        cin >> N >> a >> b >> da >> db;
        midl = 0;
        fill(dep, dep + N + 1, 0);
        fill(verts, verts + N + 1, vector<int>());

        for (int i = 1; i < N; ++i) {
            int x, y;
            cin >> x >> y;
            verts[x].push_back(y);
            verts[y].push_back(x);
        }
        dfs(a, 0);
        if (dep[b] <= da || midl <= 2 * da || db <= da * 2) {
            cout << "Alice" << endl;
        } else {
            cout << "Bob" << endl;
        }

    }
    return 0;
}
