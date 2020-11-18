#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 201;
int head[maxn];
int f[maxn][maxn];
int main(int argc, char *argv[])
{
    int N;
    cin >> N;
    copy_n(istream_iterator<int>(cin), N, head);
    copy(head, head + N, head + N);
    for (int k = 1; k < N; ++k) {
        for (int i = 0; i + k < 2 * N; ++i) {
            const int j = i + k;
            for (int s = i + 1; s <= j; ++s)
                f[i][j] = max(f[i][j], f[i][s - 1] + f[s][j] + head[i] * head[s] * head[j + 1]);
        }
    }
    int ans = 0;
    for (int i = 0; i < N; ++i)
        ans = max(ans, f[i][i + N - 1]);
    cout << ans << endl;
    return 0;
}
