#include <bits/stdc++.h>
using namespace std;
const static int maxd = 10, maxst = (1 << maxd);
const static int maxn = 2e7 + 1;
int bucket[maxst], ta[maxn];
int main()
{
    freopen("number.in", "r", stdin);
    freopen("number.out", "w", stdout);
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        ta[i] = ta[i / 10] | (1 << (i % 10));
        ++bucket[ta[i]];
    }
    long long ans = 0;
    for (int i = 1; i <= n; ++i)
        ans += bucket[ta[i]] - 1;
    cout << ans / 2 << endl;
    return 0;
}