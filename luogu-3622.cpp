#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 5e4 + 1, maxm = 1e4 + 1;
constexpr unsigned maxst = (1 << 5) - 1;

int val[maxm][maxst + 1], f[maxm][maxst + 1];
inline unsigned getst(int x) {return (1u << (x));}
int main(int argc, char *argv[])
{
    int N, C;
    cin >> N >> C;
    for (int i = 0; i < C; ++i) {
        int E;
        cin >> E;
        int f, l, t;
        unsigned like = 0, fear = 0;
        cin >> f >> l;
        for (int i = 0; i < f; ++i) {
            cin >> t;
            if (t < E)
                t += N;
            fear |= getst(t - E);
        }
        for (int i = 0; i < l; ++i) {
            cin >> t;
            if (t < E)
                t += N;
            like |= getst(t - E);
        }
        for (unsigned j = 0; j <= maxst; ++j)
            if ((like & ~j) || (fear & j))
                ++val[E][j];
    }
    int ans = 0;
    for (unsigned stst = 0; stst <= maxst; ++stst) {
        memset(f, -0x3f, sizeof(f));
        f[0][stst] = 0;
        for (int i = 1; i <= N; ++i)
            for (unsigned s = 0; s <= maxst; ++s)
                f[i][s] = max(f[i - 1][(s << 1) & maxst], f[i - 1][((s << 1) & maxst) | 1]) + val[i][s];
        ans = max(ans, f[N][stst]);
    }
    cout << ans << endl;
    return 0;
}
