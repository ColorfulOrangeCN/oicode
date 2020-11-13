#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e5 + 5;
typedef long long inte;
inte A[maxn];
int main()
{
    inte n, d, k, y;
    cin >> n >> A[1] >> d >> k >> y;
    inte tot = 0;
    for (int i = 2; i <= n; ++i)
        A[i] = A[i - 1] + d;
    //copy(A + 1, A + n + 1, ostream_iterator<int>(cout, " "));
    for (int i = 1; i <= n; ++i)
        tot += A[i];
    inte sum = 0;
    unsigned long long ans = ~0ull;
    for (int i = n; i; --i) {
        sum += A[i];
        if (y < tot - sum)
            continue;
        const inte z = min((y - tot + sum) / (n - i + 1), A[i]);

        inte rz = 0;

        for (int i = 60; i >= 0; --i) {
            if ((k & (1ll << i)) != 0 && rz + (1ll << i) <= z)
                rz += (1ll << i);
        }
        ans = min(ans, (unsigned long long)(n - i + 1) * ((rz ^ k) + k - rz));
    }
    cout << ans << endl;
    return 0;
}
