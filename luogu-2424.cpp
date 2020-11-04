#include <bits/stdc++.h>
using namespace std;
typedef long long inte;
#define int long long
inte calc(int x) {
    inte ans = 0;
    int i = 1;
    while (i <= x) {
        const int j = x / (x / i);
        ans += inte(x / i) * (i + j) * (j - i + 1) / 2;
        i = j + 1;
    }
    return ans;
}

signed main()
{
    int x, y;
    cin >> x >> y;
    cout << -calc(x - 1) + calc(y) << endl;
    return 0;
} 
