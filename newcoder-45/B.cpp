#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e6 + 1;
int N, K;
int W[maxn];
vector<tuple<int, int>> verts[maxn];
long long ans = 0;
int dfs(int u, int la) {
    int val = W[u] % K;
    for (auto [v, ww] : verts[u]) {
        if (v == la)
            continue;
        int t = dfs(v, u);
        if (t) {
            (val += t) %= K;
            ans += ww;
        }
    }
    return val;
}
int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    cin >> N >> K;
    copy_n(istream_iterator<int>(cin), N, W + 1);
    for (int i = 1; i < N; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        verts[a].push_back(make_tuple(b, c));
        verts[b].push_back(make_tuple(a, c));
    }
    dfs(1, 0);
    cout << ans << endl;
    return 0;
}
