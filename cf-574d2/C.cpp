#include <bits/stdc++.h>
using namespace std;
typedef long long inte;
const static int maxn = 1e5 + 1;
int H[maxn][2];
inte f[maxn][2];

int main(int argc, char *argv[])
{
    int N;
    cin >> N;
    for (int i = 1; i <= N; ++i)
        cin >> H[i][0];
    for (int i = 1; i <= N; ++i)
        cin >> H[i][1];
    for (int i = 1; i <= N; ++i) {
        f[i][0] = max(f[i - 1][1] + H[i][0], f[i - 1][0]);
        f[i][1] = max(f[i - 1][0] + H[i][1], f[i - 1][1]);
    }
    cout << max(f[N][0], f[N][1]) << endl;
    return 0;
}
