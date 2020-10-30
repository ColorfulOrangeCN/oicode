#include <bits/stdc++.h>
using namespace std;

typedef long long inte;

const static int maxn = 2e5 + 1;
const static inte mods = 1e9 + 7;

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

int K, N, M;
int L[maxn * 2][2], R[maxn * 2][2];
int ll[maxn * 2][2];

int plc[maxn * 2], pc;

inline int getid(int x)
{
    return lower_bound(plc + 1, plc + pc + 1, x) - plc;
}

inline int& letmax(int& l, int r)
{
    return (l < r ? l = r : l);
}

inte f[maxn * 2], g[maxn * 2], h[maxn * 2];

inte sf[maxn * 2], sg[maxn * 2], sh[maxn * 2];

int main()
{
    cin >> K >> N >> M;
    plc[++pc] = K, plc[++pc] = 0;
    for (int i = 1; i <= N; ++i)
        cin >> L[i][0] >> R[i][0], plc[++pc] = L[i][0] - 1, plc[++pc] = R[i][0];
    for (int i = 1; i <= M; ++i)
        cin >> L[i][1] >> R[i][1], plc[++pc] = L[i][1] - 1, plc[++pc] = R[i][1];
    sort(plc + 1, plc + pc + 1);
    pc = unique(plc + 1, plc + pc + 1) - plc - 1;
    for (int i = 1; i <= N; ++i) {
        R[i][0] = getid(R[i][0]);
        L[i][0] = getid(L[i][0] - 1);
        letmax(ll[R[i][0]][0], L[i][0] + 1);
    }
    for (int i = 1; i <= M; ++i) {
        R[i][1] = getid(R[i][1]);
        L[i][1] = getid(L[i][1] - 1);
        letmax(ll[R[i][1]][1], L[i][1] + 1);
    }
    h[1] = sh[1] = ll[1][0] = ll[1][1] = 1;
    for (int i = 2; i <= pc; ++i) {
        ll[i][0] = max(ll[i][0], ll[i - 1][0]);
        ll[i][1] = max(ll[i][1], ll[i - 1][1]);
        f[i] = ((sg[i - 1] - sg[ll[i][1] - 1]) + sh[i - 1] - sh[ll[i][1] - 1]) % mods;
        g[i] = ((sf[i - 1] - sf[ll[i][0] - 1]) + sh[i - 1] - sh[ll[i][0] - 1]) % mods;
        h[i] = (f[i - 1] + g[i - 1] + h[i - 1]) % mods * (fpow(2, plc[i] - plc[i - 1]) - 2 + mods) % mods;
        sf[i] = (sf[i - 1] + f[i]) % mods;
        sg[i] = (sg[i - 1] + g[i]) % mods;
        sh[i] = (sh[i - 1] + h[i]) % mods;
    }
    // OAcopy(f + 1, f + pc + 1, ostream_iterator<inte>(cout, " "));
    cout << ((f[pc] + g[pc] + h[pc]) % mods + mods) % mods;
    return 0;
}
