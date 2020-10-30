#include <bits/stdc++.h>
using namespace std;
const int maxn = 1001, maxp = 1e4+1;
int f[maxp];

int A[maxn], B[maxn], C[maxn];

int main()
{
    int T;
    cin >> T;
    while(T--) {
        memset(f, 0x3f, sizeof(f));
        int N, P;
        cin >> N >> P;
        for (int i = 1; i <= N; ++i)
            cin >> A[i];
        for (int i = 1; i <= N; ++i)
            cin >> B[i];
        for (int i = 1; i <= N; ++i)
            cin >> C[i];
        f[0] = 0;
        for (int i = 1; i <= N; ++i) {
                for (int k = P; k >= 0; --k)
                    for (int j = A[i]; j <= B[i] && k >= j; ++j)
                        f[k] = min(f[k], f[k - j] + C[i]);
        }
        if (f[P] >= 0x3f3f3f3f)
            cout << "IMPOSSIBLE!!!" << endl;
        else
            cout << f[P] << endl;
    }
    return 0;
}
