#include <bits/stdc++.h>
using namespace std;
typedef long long inte;
const int maxn = 3e5 + 2;
const inte mods = 998244353;
inte A[maxn];

inte fpow(inte x, inte p) {
    inte res = 1;
    while (p) {
        if (p & 1)
            (res *= x) %= mods;
        (x *= x) %= mods;
        p >>= 1;
    }
    return res;
}

inte fac[maxn];

int main()
{
    int N;
    cin >> N;
    inte fac = 1;
    for (int i = 2 * N - 1; i >= N + 1; --i)
        (fac *= i) %= mods;
    for (int i = 1; i < N; ++i)
        (fac *= fpow(i, mods - 2)) %= mods;
    (fac *= 2) %= mods;
    inte ans = 0;
    for (int i = 1; i <= 2 * N; ++i) {
        cin >> A[i];
    }
    sort(A + 1, A + 2 * N + 1);
    for (int i = 1; i <= N; ++i)
        (ans -= fac * A[i]) %= mods;
    for (int i = N + 1; i <= 2 * N; ++i)
        (ans += fac * A[i]) %= mods;
    cout << (ans + mods) % mods << endl;
    return 0;
}
