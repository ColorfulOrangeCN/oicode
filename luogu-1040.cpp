#include <bits/stdc++.h>
using namespace std;
const static int maxn = 50;
int f[maxn][maxn], plc[maxn][maxn];
int A[maxn];

void dfs(int l, int r)
{
    if (l > r)
        return;
    if (l == r) {
        cout << l << ' ';
    } else {
        const int mid = plc[l][r];
        cout << mid << ' ';
        dfs(l, mid - 1);
        dfs(mid + 1, r);
    }
}

int main()
{
    int N;
    cin >> N;
    for (int i = 0; i <= N + 1; ++i)
        for (int j = 0; j <= N + 1; ++j)
            f[i][j] = 1;
    for (int i = 1;i <= N; ++i)
        cin >> A[i], f[i][i] = A[i];
    for (int k = 1; k < N; ++k) {
        for (int i = 1; i <= N - k; ++i) {
            const int j = i + k;
            for (int s = i; s <= j; ++s) {
                const int v = f[i][s - 1] * f[s + 1][j] + A[s];
                if (f[i][j] < v) {
                    f[i][j] = v;
                    plc[i][j] = s;
                }
            }
        }
    }
    cout << f[1][N] << endl;
    dfs(1, N);
    return 0;
}
