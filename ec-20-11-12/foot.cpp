#include <bits/stdc++.h>
using namespace std;

const static int maxn = 1e5 + 1;
typedef long long inte;
const static inte mods = 1e9 + 7;
string str[maxn];
inte f[maxn];
int main()
{
    freopen("foot.in", "r", stdin);
    freopen("foot.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    for (int i = 1; i <= N; ++i)
        cin >> str[i];
    f[0] = f[1] = 1;
    for (int i = 2; i <= N; ++i) {
        f[i] = f[i - 1];
        if (str[i] != str[i - 1])
            (f[i] += f[i - 2]) %= mods;
    }
    cout << f[N] << endl;
    return 0;
}