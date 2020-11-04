#include <bits/stdc++.h>
using namespace std;

signed main()
{
    int a1, a2, k1, k2, n;
    cin >> a1 >> a2 >> k1 >> k2 >> n;
    if (k1 > k2)
        swap(a1, a2), swap(k1, k2);
    if (n > a1 * (k1 - 1) + a2 * (k2 - 1)) {
        cout << n - a1 * (k1 - 1) - a2 * (k2 - 1);
    } else {
        cout << 0;
    }
    cout << ' ';
    if (a1 * k1 < n) {
        cout << a1 + (n - a1 * k1) / k2; 
    } else {
        cout << n / k1;
    }
    return 0;
}
