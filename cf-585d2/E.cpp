#include <bits/stdc++.h>
using namespace std;
const static int maxn = 4e5 + 2, maxc = 20;
typedef long long inte;

vector<int> blk[21];

inline inte calc(int a, int b)
{
    inte res = 0;
    for (int i = 0; i < blk[a].size(); ++i)
        res += lower_bound(blk[b].begin(), blk[b].end(), blk[a][i]) - blk[b].begin();
    return res;
}

inte v[maxc][(1 << 20)], f[(1 << 20)];

#define lowbit(x) ((x) & (-(x)))

int N;

signed main()
{
    cin >> N;
    for (int i = 1; i <= N; ++i) {
        int a;
        cin >> a;
        blk[a - 1].push_back(i);
    }
    const int maxst = (1 << maxc);
    for (int i = 0; i < maxc; ++i) {
        for (int j = 0; j < maxc; ++j) {
            if (i != j)
                v[i][1 << j] = calc(j, i);
        }
    }
    for (int i = 0; i < maxc; ++i)
        for (int s = 1; s < maxst; ++s)
            v[i][s] = v[i][s ^ lowbit(s)] + v[i][lowbit(s)];
    memset(f, 0x3f, sizeof(f));
    f[0] = 0;
    for (int s = 1; s < maxst; ++s) {
        for (int i = 0; i < maxc; ++i) {
            if ((1 << i) & s) {
                f[s] = min(f[s ^ (1 << i)] + v[i][s ^ (1 << i)], f[s]);
            }
        }
    }
    cout << f[maxst - 1] << endl;
    return 0;
}

