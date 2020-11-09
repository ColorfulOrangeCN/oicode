#include <bits/stdc++.h>
using namespace std;
const static int maxm = 1e4 + 1;
int N, M, C;

int f[maxm] = {0}, g[maxm];

inline int val(int a, int b, int c, int x)
{
    return (a * x + b) * x + c;
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> N >> M >> C;
    for (int i = 0; i < N; ++i) {
        int v, w, d;
        cin >> v >> w >> d;
        int k = 1, kv = v, kw = w;
        while (k <= d) {
            for (int j = C; j >= kv; --j)
                f[j] = max(f[j], f[j - kv] + kw);
            if (C <= kv)
                break;
            d -= k;
            k <<= 1;
            kv <<= 1;
            kw <<= 1;
        }
        const int dv = d * v, dw = d * w;
        for (int j = C; j >= dv; --j)
            f[j] = max(f[j], f[j - dv] + dw);
    }
    for (int i = 0; i < M; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        for (int j = 0; j <= C; ++j)
            g[j] = val(a, b, c, j);
        for (int j = C; j >= 0; --j)
            for (int k = 0; j - k >= 0; ++k)
                f[j] = max(f[j], f[j - k] + g[k]);
    }
    cout << *max_element(f, f + C + 1) << endl;
    return 0;
}
