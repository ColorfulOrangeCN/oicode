#include <bits/stdc++.h>
using namespace std;

const int maxn = 2020;
int f[maxn][maxn];
int main(int argc, char *argv[])
{
    string a, b;
    cin >> a >> b;
    memset(f, 0x3f, sizeof(f));
    f[0][0] = 0;
    for (int i = 0; i <= a.length(); ++i) {
        for (int j = 0; j <= b.length(); ++j) {
            if (i)
                f[i][j] = min(f[i][j], f[i - 1][j] + 1);
            if (j)
                f[i][j] = min(f[i][j], f[i][j - 1] + 1);
            if (i && j)
                f[i][j] = min(f[i][j], f[i - 1][j - 1] + (a[i - 1] != b[j - 1]));
        }
    }
    cout << f[a.length()][b.length()];
    return 0;
}
