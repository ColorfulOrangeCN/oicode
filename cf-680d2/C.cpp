#include <bits/stdc++.h>
using namespace std;

typedef long long inte;

const int maxn = 1e5;

inte divor[maxn], dc = 0;
void divi(inte x) {
    inte t = sqrt(x);
    for (int i = 2; i <= t; ++i) {
        if (x % i == 0) {
            divor[++dc] = i;
            divor[++dc] = x;
            while (x % i == 0)
                x /= i;
        }
    }
    if (x != 1)
        divor[++dc] = x;
}

int main(int argc, char *argv[])
{
    int T;
    cin >> T;
    while(T--) {
        inte p, q;
        cin >> p >> q;
        if (p % q != 0) {
            cout << p << endl;
        } else {
            dc = 0;
            divi(q);
            inte ans = 0;
            for (int i = 1; i <= dc; ++i) {
                inte t = p;
                while (t % q == 0)
                    t /= divor[i];
                ans = max(t, ans);
            }
            cout << ans << endl;
        }
    }
    return 0;
}
