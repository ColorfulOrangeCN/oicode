#include <bits/stdc++.h>
using namespace std;

#define int long long

const static int maxn = 1e5 + 2;

signed main(signed argc, char *argv[])
{
    static int L[maxn], P[maxn];
    int M, N;
    cin >> N >> M;
    for (int i = 1; i <= M; ++i)
        cin >> L[i];
    int suml = 0, maxr = 0;
    for (int i = 1; i <= M; ++i) {
        suml += L[i];
        maxr = max(maxr, i + L[i] - 1);
    } 
    if (suml < N || maxr > N) {
        cout << "-1" << endl;
    } else {
        static int suf[maxn] = {};
        for (int i = M; i; --i)
            suf[i] = suf[i + 1] + L[i];
        P[1] = 1;
        for (int i = 2; i <= M; ++i) {
            if (i + suf[i] - 1 >= N)
                P[i] = i;
            else
                P[i] = N - suf[i] + 1;
        }
        copy(P + 1, P + M + 1, ostream_iterator<int>(cout, " "));
    }
    return 0;
}
