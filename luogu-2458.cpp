#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e4 + 1;
vector<int> verts[maxn];
int f[maxn][3], K[maxn];
void tdp(int u) {
    f[u][1] = K[u];
    int del = 0x3f3f3f3f;
    for (int v : verts[u]) {
        tdp(v);
        f[u][0] += min(f[v][1], f[v][2]);
        f[u][1] += min({f[v][0], f[v][1], f[v][2]});
        del = min(del, max(f[v][1] - f[v][2], 0));
    }
    f[u][2] = f[u][0] + del;
}
int main(int argc, char *argv[])
{
    int N;
    cin >> N;
    static int deg[maxn] = {0};
    for (int t = 1; t <= N; ++t) {
        int i;
        cin >> i;
        cin >> K[i];
        int M;
        cin >> M;
        if (M)
            copy_n(istream_iterator<int>(cin), M, back_inserter(verts[i]));
        for (int v : verts[i])
            ++deg[v];
    }
    for (int i = 1; i <= N; ++i) {
        if (!deg[i]) {
            tdp(i);
            cout << min(f[i][1], f[i][2]) << endl;
            break;
        }
    }
    return 0;
}
