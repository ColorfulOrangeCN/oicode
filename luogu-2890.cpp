#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 2001;
int main(int argc, char *argv[])
{
    static int f[maxn][maxn] = {};
    static int spd[maxn] = {};
    int N, M;
    cin >> N >> M;
    string str;
    cin >> str;
    for (int i = 0; i < N; ++i) {
        char c;
        int a, b;
        cin >> c >> a >> b;
        spd[c] = min(a, b);
    }
    for (int k = 1; k < M; ++k) {
        for (int i = 1; i + k <= M; ++i) {
            const int j = i + k;
            if (str[i - 1] == str[j - 1])
                f[i][j] = f[i + 1][j - 1];
            else
                f[i][j] = min(f[i + 1][j] + spd[str[i - 1]], f[i][j - 1] + spd[str[j - 1]]);
        }
    }
    cout << f[1][M] << endl;
    return 0;
}
