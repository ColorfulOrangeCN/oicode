#include <bits/stdc++.h>
using namespace std;
int N, K;
const static int maxn = 3e5 + 1;
int A[maxn];
int f[maxn][2];
int main()
{
    freopen("wave.in", "r", stdin);
    freopen("wave.out", "w", stdout);
    cin >> N >> K;
    int tot = 0;
    for (int i = 1; i <= N; ++i) {
        cin >> A[i];
    }  
    f[1][1] = 1;
    int ans = 0;
    for (int i = 2; i <= N; ++i) {
        f[i][1] = 1;
        for (int k = 1; k < i; ++k) {
            if (A[k] <= A[i] - K)
                f[i][0] = max(f[i][0], f[k][1] + 1);
            if (A[k] >= A[i] + K)
                f[i][1] = max(f[i][1], f[k][0] + 1);
        }
        ans = max(ans, max(f[i][1], f[i][0]));
    }
    cout << ans << endl;
    return 0;
}
