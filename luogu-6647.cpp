#include <bits/stdc++.h>
using namespace std;
typedef long long inte;
constexpr static int maxn = 1e6 + 5, mlg = 21;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, K;
    static int A[maxn];
    static inte f[maxn];
    cin >> N >> K;
    auto get_upper = [K](int x){return (x + K - 1) / K;};
    
    copy_n(istream_iterator<int>(cin), N, A + 1);

    static int st[maxn][mlg], logger[maxn];
    for (int i = 1; i <= N; ++i)
        st[i][0] = A[i];
    for (int i = 2; i <= N; ++i)
        logger[i] = logger[i >> 1] + 1;
    for (int k = 0; k < logger[N]; ++k)
        for (int i = 1; i + (1 << k) <= N; ++i)
            st[i][k + 1] = max(st[i][k], st[i + (1 << k)][k]);
    auto getmax =
        [&](int l, int r) {
            const int ll = logger[r - l + 1];
            return max(st[l][ll], st[r - (1 << ll) + 1][ll]);
        };
    auto calc =
        [&](int cur, int p) {
            return f[p] + getmax(p + 1, cur);
        };
    
    deque<pair<int, int>> decs;
    decs.push_back(make_pair(0, 1));
    
    for (int i = 1; i <= N; ++i) {
        const int k = get_upper(i);
        while (decs.size() > 1 && decs[1].second <= i)
            decs.pop_front();
        f[i] = calc(i, decs.front().first);
        int rightest = i + K;
        while (!decs.empty() && decs.back().second >= k * K + 1 && calc(decs.back().second, decs.back().first) < calc(decs.back().second, i))
            rightest = decs.back().second, decs.pop_back();
        if (!decs.empty()) {
            int L = max(decs.back().second, k * K + 1), R = min(rightest - 1, N);
            while (L <= R) {
                const int mid = (L + R) / 2;
                if (calc(mid, decs.back().first) >= calc(mid, i)) {
                    L = mid + 1;
                } else {
                    R = mid - 1;
                    rightest = mid;
                }
            }
        }
        if (rightest <= N)
            decs.push_back(make_pair(i, rightest));
    }

    cout << f[N] << endl;
    return 0;
}

