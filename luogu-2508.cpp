#include <bits/stdc++.h>
using namespace std;
typedef long long inte;

inte ans = 0;
inte r;
inte gcd(inte x, int y)
{
    if (x == 0) return y;
    else return gcd(y % x, x);
}
inline void solve_s_t(int d)
{
    for (inte s = 1; s * s <= 2 * r / d; ++s) {
        const inte t = sqrt(2 * r / d - s * s);
        if (gcd(s, t) == 1 && s * s + t * t == 2 * r / d) {
            const inte x = (s * s - t * t) / 2 * d;
            const inte y = (d * s * t);
            if (x > 0 && y > 0 && x * x + y * y == r * r)
                ans += 2;
        }
    }
}

int main(int argc, char *argv[])
{
    cin >> r;
    for (inte i = 1; i * i <= 2 * r; ++i) {
        if ((2 * r) % i == 0) {
            solve_s_t(i);
            if (i * i != 2 * r)
                solve_s_t(2 * r / i);
        }
    }
    cout << (ans + 1) * 4;
    return 0;
}
