#include <bits/stdc++.h>
using namespace std;
typedef long long inte;
const static int maxn = 1e6 + 1;
const static inte mods = 998244353;

int C[maxn] = {0};
#define lowbit(x) ((x) & (-(x)))
int N;
inline void build()
{
    for (int i = 1; i <= N; ++i)
        C[i] = lowbit(i);
}
inline void add(int x, int v)
{
    while (x <= N) {
        C[x] += v;
        x += lowbit(x);
    }
}
inline int query(int x)
{
    int res = 0;
    while (x) {
        res += C[x];
        x -= lowbit(x);
    }
    return res;
}

inte fact[maxn];

int main(int argc, char *argv[])
{
    inte id = 0;
    cin >> N;
    fact[0] = 1;
    for (int i = 1 ; i < N; ++i)
        fact[i] = (fact[i - 1] * i) % mods;
    build();
    for (int i = N; i; --i) {
        int a;
        cin >> a;
        (id += (query(a) - 1) * fact[i - 1]) %= mods;
        add(a, -1);
    }
    cout << (id + 1 + mods) % mods << endl;
    return 0;
}
