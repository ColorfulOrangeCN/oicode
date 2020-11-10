#include <bits/stdc++.h>
using namespace std;

const static int maxn = 501, maxm = 100;

int f[maxn][maxm];
int t[maxn], st[maxn];
#define letmin(l, r) ((l) > (r) ? ((l) = (r)) : (l))
int main(int argc, char *argv[])
{
    int N, M;
    cin >> N >> M;
    for (int i = 1; i <= N; ++i)
        cin >> t[i];
    sort(t + 1, t + N + 1);
    for (int i = 1; i <= N; ++i)
        st[i] = st[i - 1] + t[i];
    memset(f, 0x3f, sizeof(f));
    for (int k = 0; k < M; ++k)
        f[0][k] = 0;
    t[0] = -10000000;
    for (int i = 1; i <= N; ++i) {
        for (int k = 0; k < M; ++k) {
            for (int j = 0; j < i; ++j) {
                const int s = min(t[i] + k - t[j] - M, M - 1);
                if (s >= 0)
                    letmin(f[i][k], f[j][s] + ((k + t[i]) * (i - j) + st[j] - st[i]));
            }
            //cout << f[i][k] << ' ';
            if (k != 0)
                letmin(f[i][k], f[i][k - 1]);
        }
        //cout << endl;
    }
    cout << f[N][M - 1] << endl;
    return 0;
}
