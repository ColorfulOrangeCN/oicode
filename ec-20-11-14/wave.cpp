#include <bits/stdc++.h>
using namespace std;
int N, K;
const static int maxn = 3e5 + 1;
int A[maxn];
int f[maxn][2];
int plc[maxn * 3];
int tot = 0;
struct BIT {
    int c[maxn * 3];
    BIT(){memset(c, -0x3f, sizeof(c));}
    inline int lowbit(int x) {return x & (-x);}
    void maxium(int x, int v) {
        while (x <= tot) {
            c[x] = std::max(c[x], v);
            x += lowbit(x);
        }
    }
    int query(int x) {
        int res = -0x3f3f3f3f;
        while (x) {
            res = std::max(res, c[x]);
            x -= lowbit(x);
        }
        return res;
    }
} t0, t1;
inline int getid(int x)
{
    return lower_bound(plc + 1, plc + tot + 1, x) - plc;
}
int main()
{
    freopen("wave.in", "r", stdin);
    freopen("wave.out", "w", stdout);
    cin >> N >> K;
    for (int i = 1; i <= N; ++i) {
        cin >> A[i];
        plc[++tot] = A[i];
        plc[++tot] = A[i] + K;
        plc[++tot] = A[i] - K;
    }
    sort(plc + 1, plc + tot + 1);
    int ans = 0;
    for (int i = 1; i <= N; ++i) {
        f[i][1] = 1;
        const int lp = getid(A[i] - K), cp = getid(A[i]), rp = getid(A[i] + K);
        f[i][0] = max(f[i][0], t1.query(lp) + 1);
        f[i][1] = max(f[i][1], t0.query(tot - rp + 1) + 1);
        t0.maxium(tot - cp + 1, f[i][0]);
        t1.maxium(cp, f[i][1]);
        ans = max(ans, max(f[i][1], f[i][0]));
    }
    cout << ans << endl;
    return 0;
}