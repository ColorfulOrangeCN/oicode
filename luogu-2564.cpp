#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e6;
typedef pair<int, int> One;
int vis[60], cnt = 0;
One os[maxn];
int main() {
    int N, K;
    cin >> N >> K;
    int tot = 0;
    for (int i = 0; i < K; ++i) {
        int t;
        cin >> t;
        for (int j = 0; j < t; ++j)
            cin >> os[tot].first, os[tot++].second = i;
    }
    assert(tot == N);
    sort(os, os + N);
    tot = 0;
    int ans = ~0u>>1;
    for (int i = 0; i < N && tot < N; ++i) {
        while (cnt < K && tot < N) {
            ++vis[os[tot].second];
            if (vis[os[tot].second] == 1)
                ++cnt;
            ++tot;
        }
        if (cnt >= K)
            ans = min(ans, os[tot - 1].first - os[i].first);
        --vis[os[i].second];
        if (!vis[os[i].second])
            --cnt;
    }
    cout << ans << endl;
    return 0;
}
