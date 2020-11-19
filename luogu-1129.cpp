#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 201;
int g[maxn][maxn];
int N;
bool vis[maxn];
int mat[maxn * 2];
bool match(int u) {
    for (int i = 1; i <= N; ++i) {
        if (g[u][i] && !vis[i]) {
            vis[i] = true;
            if (!mat[i] || match(mat[i])) {
                mat[i]= u;
                return true;
            }
        }
    }
    return false;
}
int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> N;
        memset(mat, 0, sizeof(mat));
        for (int i = 1; i <= N; ++i)
            for (int j = 1; j <= N; ++j)
                cin >> g[i][j];
        int ans = 0;
        for (int i = 1; i <= N; ++i) {
            memset(vis, 0, sizeof(vis));
            if (match(i))
                ++ans;
        }
        cout << (ans == N ? "Yes" : "No") << endl;
    }
    return 0;
}
