#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 3001;
int f[maxn][maxn] = {};
int main()
{
    static int col[maxn];
    int N;
    cin >> N;
    copy_n(istream_iterator<int>(cin), N, col + 1);
    for (int k = 1; k < N; ++k) {
        for (int i = 1; i + k <= N; ++i) {
            const int j = i + k;
            if (col[i] == col[j])
                f[i][j] = f[i + 1][j - 1];
            else
                f[i][j] = min({f[i + 1][j], f[i + 1][j - 1], f[i][j - 1]}) + 1;
        }
    }
    cout << f[1][N] << endl;
    return 0;
}
