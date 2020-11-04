#include <bits/stdc++.h>
using namespace std;
const static int maxn = 2e5 + 1;
int N;
int A[maxn], S[maxn];
typedef long long inte;
signed main()
{
    cin >> N;
    S[0] = 1;
    int cnt0 = 0, cnt1 = 1;
    inte ans0 = 0, ans1 = 0;
    for (int i = 1; i <= N; ++i) {
        cin >> A[i];
        A[i] = A[i] > 0 ? 1 : -1;
        S[i] = S[i - 1] * A[i];
        if (S[i] > 0)
            ans0 += cnt0, ans1 += cnt1, ++cnt1;
        else
            ans1 += cnt0, ans0 += cnt1, ++cnt0;
    }
    cout << ans0 << ' ' << ans1 << endl;
    return 0;
}

