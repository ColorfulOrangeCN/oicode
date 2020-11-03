#include <bits/stdc++.h>
using namespace std;

typedef long long inte;

const static int maxn = 1e5 + 1;
const static inte mods = 998244353;

int A[maxn], cnt[11];
inte p10[11];

int cntBit(int x)
{
    int c = 0;
    while(x) {
        ++c;
        x /= 10;
    }
    return c;
}

inline inte p2(inte x) {return x * x % mods;}

inte sufs[12] = {0};

int main(int argc, char *argv[])
{
    int N;
    cin >> N;
    p10[0] = 1;
    for (int i = 1; i <= 10; ++i)
        p10[i] = (p10[i - 1] * 10);
    for (int i = 1; i <= N; ++i) {
        cin >> A[i];
        ++cnt[cntBit(A[i])];
    }
    for (int i = 10; i >= 1; --i) {
        sufs[i] = sufs[i + 1] + cnt[i];
    }
    sort(A + 1, A + N + 1);
    inte ans = 0;
    for (int i = 1; i <= N; ++i) {
        int cb = cntBit(A[i]), x = A[i];
//        cout << cnt[cb] << endl;
        inte acm = 0;
        for (int j = 1; j <= cb; ++j) {
            (acm += (x % 10) * 11 % mods * p2(p10[j - 1]) % mods) %= mods;
            x /= 10;
            (ans += (acm + x * p2(p10[j]) * 2) % mods * cnt[j] % mods) %= mods;
//            cout << ans << endl;
        }
        (ans += sufs[cb + 1] * acm) %= mods;
//        cout << acm << ' ' << ans << endl;
    }
    cout << ans << endl;
    return 0;
}
