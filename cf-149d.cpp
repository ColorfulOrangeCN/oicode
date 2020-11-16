#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 705;
typedef long long inte;
constexpr inte mods = 1e9 + 7;
int match[maxn];
inte f[maxn][maxn][3][3];
bool vis[maxn][maxn][3][3];
vector<int> colck(int k) {return (!k ? vector<int>{0, 1, 2} : (k == 1 ? vector<int>{0, 2} : vector<int>{0, 1}));}
inline bool mar(int a, int b) {return (a && !b) || (b && !a);}
inte dfs(int l, int r, int cl, int cr)
{
    if (vis[l][r][cl][cr])
        return f[l][r][cl][cr];
    vis[l][r][cl][cr] = true;
    inte res = 0;
    if (r == l + 1) {
        res = mar(cl, cr);
    } else if (match[l] == r) {
        if (mar(cl, cr)) {
            auto al = colck(cl), ar = colck(cr);
            for (int ccl : al)
                for (int ccr : ar)
                    /*cerr << l << ' ' << r << " DEBUG " << ccl << ' ' << ccr << endl,*/ res += dfs(l + 1, r - 1, ccl, ccr);
        }
    } else {
        for (int i = 0; i < 3; ++i) {

                const auto con = colck(i);
                for (auto k : con)
                    res += dfs(l, match[l], cl, i) * dfs(match[l] + 1, r, k, cr);  

        }
    }
    return f[l][r][cl][cr] = res % mods;
}
char str[maxn];
int main(int argc, char *argv[])
{
    cin >> (str + 1);
    const int N = strlen(str + 1);
    stack<int> st;
    for (int i = 1; i <= N; ++i) {
        if (str[i] == '(') {
            st.push(i);
        } else {
            match[st.top()] = i;
            st.pop();
        }
    }
    match[0] = N + 1;
    auto v = colck(0);
    inte res = 0;
    for (int l : v)
        for (int r : v)
            res += dfs(1, N, l, r);
    cout << (res % mods) << endl;
    return 0;
}
