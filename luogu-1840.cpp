#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 2e5 + 2;
int lbk[maxn];
int getlb(int x)
{
    if (lbk[x] == x)
        return x;
    else
        return lbk[x] = getlb(lbk[x]);
}
int col[maxn];
int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        lbk[i] = i;
    int cnt = n;
    for (int i = 1; i <= m; ++i) {
        int l, r;
        cin >> l >> r;
        int cur = getlb(r);
        while (cur >= l) {
            if (!col[cur])
                --cnt, col[cur] = true;
            lbk[cur] = getlb(cur - 1);
            cur = lbk[cur];
        }
        cout << cnt << endl;
    }
    return 0;
}
