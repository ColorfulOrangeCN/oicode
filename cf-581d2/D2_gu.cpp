#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 1;

int P[maxn], B[maxn];

int main(int argc, char *argv[])
{
    string s, t;
    cin >> s >> t;
    int N = s.length(), M = t.length();
    for (int i = 0, p = 0; i < N && p < M; ++i) {
        if (s[i] == t[p]) {
            P[p++] = i;
        }
    }
    for (int i = N - 1, p = M - 1; i >= 0 && p >= 0; --i) {
        if (s[i] == t[p]) {
            B[p--] = i;
        }
    }
    int ans = max(B[0], N - P[M - 1] - 1);
    for (int i = 0; i < M - 1; ++i) {
        ans = max(ans, B[i + 1] - P[i] - 1);
    }
    cout << ans << endl;
    return 0;
}
