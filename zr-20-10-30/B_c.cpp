#include <bits/stdc++.h>
using namespace std;

const static int maxn = 1e5 + 1;

typedef long long inte;

int N, M;
int A[maxn], B[maxn];

inline int popcount(register int x)
{
    int res = 0;
    while (x) {
        res += (x & 1);
        x >>= 1;
    }
    return res;
}

int main(int argc, char *argv[])
{
    cin >> N >> M;
    for (int i = 1; i <= N; ++i)
        cin >> A[i];
    for (int i = 1; i <= M; ++i)
        cin >> B[i];
    int ans = 0;
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= M; ++j)
            ans += (popcount(A[i] ^ B[j]) == 2);
    cout << ans << endl;
    return 0;
}
