#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 102, maxm = 10, maxst = (1 << maxm);
int mp[maxn];
int f[maxst][maxst][2] = {{}}, popc[maxst];
int main(int argc, char *argv[])
{
    int N, M;
    cin >> N >> M;
    const int lst = (1 << M) - 1;
    for (int i = 1; i <= N; ++i) {
        int cur = 0;
        for (int j = 0; j < M; ++j) {
            char c;
            cin >> c;
            if (c == 'H')
                cur |= (1 << j);
        }
        mp[i + 1] = lst & (~cur);
    }
    for (int i = 0; i <= lst; ++i)
        popc[i] = __builtin_popcount(i);
    bool tg = 0;
    for (int i = 1; i <= N; ++i) {
        // cout << "gu" << endl;
        for (int s = 0; s <= lst; ++s)
            for (int k = 0; k <= lst; ++k)
                f[s][k][tg] = 0;
        for (int j = mp[i - 1]; j >= 0; j = (j - 1) & (mp[i - 1])) {
            const int lim = (lst & ~j & mp[i]);
            for (int k = lim; k >= 0; k = lim & (k - 1)) {
                const int rl = lst & (~j) & (~k) & mp[i + 1];
                for (int s = rl; s >= 0; s = (s - 1) & rl) {
                    if ((s & (s << 1)) || (s & (s << 2)))
                        continue;
                    f[s][k][tg] = max(f[s][k][tg], f[k][j][tg ^ 1] + popc[s]);
                    if (!s)
                        break;
                }
                if (!k)
                    break;
            }
            if (!j)
                break;
        }
        tg ^= 1;
    }
    int ans = 0;
    for (int j = 0; j <= lst; ++j)
        for (int k = 0; k <= lst; ++k)
            ans = max(ans, f[j][k][tg ^ 1]);
    cout << ans << endl;
    return 0;
}
