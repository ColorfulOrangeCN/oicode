#include <bits/stdc++.h>
using namespace std;
typedef long long inte;
constexpr int maxn = 5e5 + 1;
int N, M;

inte presum[maxn] = {0};
inte a[maxn];
struct DP {
    inte v;
    int c;
} f[maxn];
inline bool operator < (const DP& x, const DP& y) {return x.v < y.v;}
inline DP operator + (const DP& x, const DP& y) {return {x.v + y.v, x.c + y.c};}
inline inte w(int l, int r)
{
    const int mid = (l + r) / 2;
    return presum[r] + presum[l - 1] - 2 * presum[mid] - inte(a[mid]) * (r + l - mid * 2 - 1);
}
inline void run(inte extrav)
{
    deque<pair<int, int>> q;
    q.push_back(make_pair(0, 0));
    f[0] = (DP){0, 0};
    auto getval =
        [&](int p, int i) {
            return f[p] + (DP){w(p + 1, i) + extrav, 1};
        };
    for (int i = 1; i <= N; ++i) {
        while (q.size() > 1 && q[1].first <= i)
            q.pop_front();
        f[i] = getval(q.front().second, i);
        q.front().first = max(q.front().first, i + 1);
        while (!q.empty() && getval(i, q.back().first).v <= getval(q.back().second, q.back().first).v)
            q.pop_back();
        if (q.empty()) {
            q.push_back(make_pair(i + 1, i));
        } else {
            int L = q.back().first + 1, R = N, res = N + 1;
            while (L <= R) {
                const int mid = (L + R) >> 1;
                if (getval(i, mid).v <= getval(q.back().second, mid).v) {
                    res = mid;
                    R = mid - 1;
                } else {
                    L = mid + 1;
                }
            }
            q.push_back(make_pair(res, i));
        }
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> N >> M;
    copy_n(istream_iterator<int>(cin), N, a + 1);
    partial_sum(a + 1, a + N + 1, presum + 1);
    inte L = 0, R = 1e8, res = 0;
    while (L <= R) {
        const inte mid = (L + R) >> 1;
        run(mid);
        if (f[N].c >= M) {
            L = mid + 1;
            res = mid;
        } else {
            R = mid - 1;
        }
    }
    run(res);
    cout << f[N].v - inte(M) * res << endl;;
    return 0;
}
