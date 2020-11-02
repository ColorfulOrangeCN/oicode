#include <bits/stdc++.h>
using namespace std;

const int maxn = 101, inf = 0x3f3f3f3f, maxm = 1e6 + 1;

int f[maxn][maxn];

template<typename T>
inline T& letmin(T& l, const T& r)
{
    return (l > r ? l = r : l);
}

int P[maxm], ans[maxm], K = 0;

int main(int argc, char *argv[])
{
    int N, M;
    cin >> N;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            char c;
            cin >> c;
            f[i][j] = c - '0';
            if (f[i][j] == 0) {
                f[i][j] = inf;
            }
        }
        f[i][i] = 0;
    }
    for (int k = 1; k <= N; ++k)
        for (int i = 1; i <= N; ++i)
            for (int j = 1; j <= N; ++j)
                letmin(f[i][j], f[i][k] + f[k][j]);
    cin >> M;
    for (int i = 1; i <= M; ++i)
        cin >> P[i];
    ans[++K] = P[1];

    for (int p = 1; p < M;) {
        int q = p + 1;
        while (q <= M && f[P[p]][P[q]] == q - p)
            ++q;
        p = q - 1;
        ans[++K] = P[p];
    }
    cout << K << endl;
    copy(ans + 1, ans + K + 1, ostream_iterator<int>(cout, " "));
    cout << endl;
    return 0;
}
