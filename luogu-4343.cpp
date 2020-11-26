#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e5 + 1;
int del[maxn];
typedef long long inte;
int ll;
int check(inte n) {
    inte cur = 0;
    int k = 0;
    for (int i = 0;i < ll; ++i) {
        cur = max(cur + del[i], 0ll);
        if (cur >= n)
            ++k, cur = 0;
    }
    //cerr << n << ' ' << k << endl;
    return k;
}

int main() {
    int k;
    cin >> ll >> k;
    copy_n(istream_iterator<int>(cin), ll, del);
    {
        inte L = 1, R = 1e9 * maxn, res = -1;
        while (L <= R) {
            const inte mid = (L + R) / 2;
            const inte v = check(mid);
            if (v > k)
                L = mid + 1;
            else
                R = mid - 1;
            if (v == k)
                res = mid;
        }
        cout << res << ' ';
    }
    {
        inte L = 1, R = 1e9 * maxn, res = -1;
        while (L <= R) {
            const inte mid = (L + R) / 2;
            const inte v = check(mid);
            if (v >= k)
                L = mid + 1;
            else
                R = mid - 1;
            if (v == k)
                res = mid;
        }
        if (res != -1)
            cout << res << endl;
    }
    return 0;
}
