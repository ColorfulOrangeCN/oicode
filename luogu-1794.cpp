#include <bits/stdc++.h>
using namespace std;
const static int maxn = 501;
int f[maxn][maxn];
int t[maxn], v[maxn], g[maxn];
int main()
{
    int V, G;
    cin >> V >> G;
    int N;
    cin >> N;
    for (int i = 1; i <= N; ++i)
        cin >> t[i] >> v[i] >> g[i];
    int ans = 0;
    for (int i = 1; i <= N; ++i)
        for (int j = V; j >= v[i]; --j)
            for (int k = G; k >= g[i]; --k)
                ans = max(ans, f[j][k] = max(f[j][k], f[j - v[i]][k - g[i]] + t[i]));
    cout << ans << endl;
    return 0;
}
