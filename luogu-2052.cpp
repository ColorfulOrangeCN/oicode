#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e6 + 1;
typedef long long inte;
vector<pair<int, int>> verts[maxn];
int N;
inte ans = 0;
int dfs(int u, int la) {
    int sz = 1;
    for (auto [v, w] : verts[u]) {
        if (v == la)
            continue;
        const int xsz = dfs(v, u);
        sz += xsz;
        ans += inte(w) * abs(N - xsz * 2);
    }
    return sz;
}
int main(int argc, char *argv[])
{
    cin >> N;
    for (int i = 1; i < N; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        verts[a].push_back(make_pair(b, c));
        verts[b].push_back(make_pair(a, c));
    }
    dfs(1, 0);
    cout << ans << endl;
    return 0;
}
