#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main()
{
    int n, a, b;
    cin >> n >> a >> b;
    int ans = 0;
    for (int i = 1, t = 1; i <= a; ++i, t *= 2)
        ans += t;
    ans += (n - a) * 1;
    cout << ans << ' ';
    ans = 0;
    int t = 1;
    for (int i = 1; i <= b; ++i, t *= 2)
        ans += t;
    ans += (n - b) * (t / 2);
    cout << ans << endl;
    return 0;
}
