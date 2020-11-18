#include <bits/stdc++.h>
using namespace std;
constexpr int maxm = 20005, maxn = 101;
int f[maxm] = {0};
int pawn[maxn][maxn] = {0};
int main(int argc, char *argv[])
{
    int S, N, M;
    cin >> S >> N >> M;
    for (int i = 0; i < S; ++i)
        for (int j = 1; j <= N; ++j)
            cin >> pawn[j][i], pawn[j][i] = pawn[j][i] * 2 + 1;
    for (int j = 1; j <= N; ++j)
        sort(pawn[j], pawn[j] + S);
    for (int k = 1; k <= N; ++k)
        for (int j = M; j; --j)
            for (int i = 0; i < S && pawn[k][i] <= j; ++i)
                f[j] = max(f[j], f[j - pawn[k][i]] + (i + 1) * k);
    cout << *max_element(f, f + M + 1) << endl;
    return 0;
}
