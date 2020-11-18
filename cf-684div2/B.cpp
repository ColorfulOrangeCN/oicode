#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 2e5 + 1;
int A[maxn];
typedef long long inte;
int main(int argc, char *argv[])
{
    int T;
    cin >> T;
    while (T--) {
        int N, K;
        cin >> N >> K;
        copy_n(istream_iterator<int>(cin), N * K, A);
        sort(A, A + N * K);
        inte ans = 0;
        const int giveup = (N + 1) / 2 - 1;
        for (int i = giveup * K; i < N * K; i += N - giveup)
            ans += A[i];
        cout << ans << endl;
    }
    return 0;
}
