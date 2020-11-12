#include <bits/stdc++.h>
using namespace std;

const static int maxn = 5e6 + 1;
typedef long long inte;
#define ull unsigned long long
const int threshold = 10000000;
ull k1, k2;
ull Rand()
{
    ull k3 = k1, k4 = k2;
    k1 = k4;
    k3 ^= (k3 << 23);
    k2 = k3 ^ k4 ^ (k3 >> 17) ^ (k4 >> 26);
    return k2 + k4;
}
int a[maxn], b[maxn]; //数组a和b
void gen(int n, ull _k1, ull _k2)
{
    k1 = _k1, k2 = _k2;
    for (int i = 1; i <= n; i++)
    {
        a[i] = Rand() % threshold + 1;
        b[i] = Rand() % threshold + 1;
    }
}
int N, M;
int t[maxn];
ull f[maxn * 3], g[maxn * 3];
int main()
{
    freopen("hand.in", "r", stdin);
    freopen("hand.out", "w", stdout);
    ull k1, k2;
    cin >> N >> M >> k1 >> k2;
    gen(N, k1, k2);
    ull ans = 0;
    for (int i = 1; i <= N; ++i)
        t[i] = a[i] + b[i];
    if (N <= 2000) {
        ull ans = 0;
        for (int i = 1; i <= N; ++i) {
            for (int j = min(i * 3, M); j; --j) {
                f[j] = max(f[j], f[j - 1] + a[i]);
                if (j >= 2) f[j] = max(f[j], f[j - 2] + a[i] + b[i]);
                if (j >= 3) f[j] = max(f[j], f[j - 3] + a[i] + b[i] + a[i]);
            }
        }
        for (int i = 1; i <= M; ++i)
            ans ^= f[i];
        cout << ans << endl;
        return 0;
    }
    sort(a + 1, a + N + 1, greater<int>());
    sort(t + 1, t + N + 1, greater<int>());
    for (int i = 2; i <= M && i <= 2 * N; i += 2)
        f[i] = f[i - 2] + t[i / 2];
    for (int i = 1; i <= M && i <= N; ++i)
        g[i] = g[i - 1] + a[i];
    int decs = 0;
    for (int i = 1; i <= M; ++i) {
        while (decs + 2 <= i && f[decs + 2] + g[i - decs - 2] > f[decs] + g[i - decs])
            decs += 2;
        const ull t = f[decs] + g[i - decs];
        ans ^= t;
    }
    cout << ans << endl;
    return 0;
}