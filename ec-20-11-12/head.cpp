#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 2e5 + 4;
typedef long long inte;
constexpr inte mods = 998244353;

vector<int> verts[maxn];

inline inte fpow(inte x, inte p) {
    inte res = 1;
    while (p) {
        if (p & 1)
            (res *= x) %= mods;
        (x *= x) %= mods;
        (p >>= 1);
    }
    return res;
}
inline inte getop(inte x) {return fpow(x, mods - 2);}

int N;

template<typename T>
inline T get_method(const T& p) {return p * (p + 1) / 2;}
inte f[maxn], g[maxn], h[maxn], sz[maxn];
void dfs(int u, int la) {
    sz[u] = f[u] = g[u] = 1;
    for (int v : verts[u]) {
        if (v == la)
            continue;
        dfs(v, u);
        sz[u] += sz[v];
		(f[u] *= (f[v] + fpow(2, get_method(sz[v])) - g[v])) %= mods;
		(g[u] *= fpow(2, get_method(sz[v]))) %= mods;
    }
}
inte ans = 0;
void dfs2(int u, int la) {
    for (int v : verts[u]) {
        if (v == la)
            continue;
        (ans += f[v] * (fpow(2, get_method(N - sz[v])) - (g[u] * getop(fpow(2, get_method(sz[v]))) % mods * fpow(2, get_method(N - sz[u])) % mods))) %= mods;
        dfs2(v, u);
    }
}

int main()
{
    freopen("head.in", "r", stdin);
    freopen("head.out", "w", stdout);
    cin >> N;
    for (int i = 1; i < N; ++i) {
        int a, b;
        cin >> a >> b;
        verts[a].push_back(b);
        verts[b].push_back(a);
    }
    dfs(1, 0);
    dfs2(1, 0);
    (ans += f[1]) %= mods;
    cout << (ans + mods) % mods << endl;
    return 0;
}