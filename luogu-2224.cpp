#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 6e3 + 1, maxt = 5, inf = 0x3f3f3f3f;

int f[maxn * maxt];

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    memset(f, 0x3f, sizeof(f));
    f[0] = 0;
    int presum = 0;
    for (int i = 1; i <= N; ++i) {

        int t1, t2, t3;
        cin >> t1 >> t2 >> t3;
        presum += max(t1, t3);
        for (int j = presum; j >= 0; --j) {
            int t = inf;
            if (t1 && j >= t1)
                t = min(t, f[j - t1]);
            if (t3 && j >= t3)
                t = min(t, f[j - t3] + t3);
            if (t2)
                t = min(f[j] + t2, t);
            f[j] = t;
        }
    }
    int ans = inf;
    for (int i = 0; i <= presum; ++i)
        ans = min(ans, max(i, f[i]));
    cout << ans << endl;
    return 0;
}

