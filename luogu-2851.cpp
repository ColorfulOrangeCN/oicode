#include <bits/stdc++.h>
using namespace std;
constexpr int maxt = 10001, maxn = 100, maxv = 121;
constexpr int p2(int v) {return v * v;}
int v[maxn], c[maxn];
int f1[maxt + p2(maxv)], f2[p2(maxv)];
int main(int argc, char *argv[])
{
    int N, T;
    cin >> N >> T;
    copy_n(istream_iterator<int>(cin), N, v);
    copy_n(istream_iterator<int>(cin), N, c);
    int ext = p2(*max_element(v, v + N));
    memset(f1, 0x3f, sizeof(f1));
    memset(f2, 0x3f, sizeof(f2));
    f1[0] = f2[0] = 0;
    for (int i = 0; i < N; ++i) {
        for (int k = 1; k <= c[i]; c[i] -= k, k *= 2) {
            for (int j = T + ext; j >= k * v[i]; --j)
                f1[j] = min(f1[j], f1[j - k * v[i]] + k);
        }
        for (int j = T + ext; j >= c[i] * v[i]; --j)
            f1[j] = min(f1[j], f1[j - c[i] * v[i]] + c[i]);
        for (int j = v[i]; j <= ext; ++j)
            f2[j] = min(f2[j], f2[j - v[i]] + 1);
    }
    int ans = 0x3f3f3f3f;
    for (int i = 0; i <= ext; ++i)
        ans = min(ans, f1[i + T] + f2[i]);
    if (ans >= 0x3f3f3f3f)
        cout << -1 << endl;
    else
        cout << ans << endl;
    return 0;
}
