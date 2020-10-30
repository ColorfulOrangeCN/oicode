#include <bits/stdc++.h>
using namespace std;

typedef long long inte;

const static int maxn = 1e5 + 1;
const static inte mods = 1000000007;

inte fpow(inte x, int p)
{
    inte res = 1;
    while (p) {
//        cout << p << endl;
        if (p & 1)
            (res *= x) %= mods;
        (x *= x) %= mods;
        p >>= 1;
    }
    return res;
}

inte f[maxn * 2], g[maxn * 2];
int K, N, M;
int L[maxn * 2][2], R[maxn * 2][2];
int pre[maxn * 2][2];
bool vis[maxn * 2][2];

int plc[maxn * 2], pc;

inline int getid(int x)
{
    return lower_bound(plc + 1, plc + pc + 1, x) - plc;
}

int main()
{
    cin >> K >> N >> M;
    plc[++pc] = K;
    for (int i = 1; i <= N; ++i)
        cin >> L[i][0] >> R[i][0], plc[++pc] = L[i][0] - 1, plc[++pc] = R[i][0];
    for (int i = 1; i <= M; ++i)
        cin >> L[i][1] >> R[i][1], plc[++pc] = L[i][1] - 1, plc[++pc] = R[i][1];
    sort(plc + 1, plc + pc + 1);
    pc = unique(plc + 1, plc + pc + 1) - plc - 1;
    for (int i = 1; i <= N; ++i) {
        L[i][0] = getid(L[i][0]), R[i][0] = getid(R[i][0]);
        ++pre[L[i][0] + 1][0], --pre[R[i][0] + 1][0];
    }
    for (int i = 1; i <= M; ++i) {
        L[i][1] = getid(L[i][1]), R[i][1] = getid(R[i][1]);
        ++pre[L[i][1] + 1][1], --pre[R[i][1] - 1][1];
    }
    for (int j = 0; j <= 1; ++j) {
        int acm = 0;
        for (int i = 1; i <= pc; ++i) {
            acm += pre[i][j];
            if (acm)
                vis[i][j] = 1;
        }
    }
    f[0] = 0;
    g[0] = 1;
    for (int i = 1; i <= pc; ++i) {
        f[i] = (f[i - 1] * fpow(2, plc[i] - plc[i - 1]) % mods + g[i - 1] * (vis[i][0] + vis[i][1])) % mods;
        g[i] = (fpow(2, plc[i]) - f[i]) % mods;
        cout << "Attention" << i << ' ' << plc[i] << endl;
        cout << f[i] << ' ' << g[i] << endl;
    }
    cout << f[pc] << endl;
    return 0;
}
