#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e5 + 1;
template<typename T>
inline T& letmax(T& l, const T& r) {return (l < r) ? (l = r) : l;}

struct BIT {
    int c[maxn], org[maxn];
    inline static int lowbit(int x) {
        return x & (-x);
    }
    inline int query(int l, int r) {
        int res = 0;
        while (r >= l) {
            letmax(res, org[r--]);
            while (r - lowbit(r) + 1 >= l) {
                res = max(res, c[r]);
                r -= lowbit(r);
            }
        }
        return res;
    }
    inline void modify(int x, int v) {
        org[x] = v;
        while (x < maxn) {
            c[x] = org[x];
            for (int i = 1; i < lowbit(x); i <<= 1)
                letmax(c[x], c[x - i]);
            // cerr << c[x] << endl;
            x += lowbit(x);
        }
    }
} bt;

struct Node {
    int dep, par, size, hson, top, dfn, w;
} nodes[maxn];

vector<pair<int, int>> verts[maxn];

void predfs(int u) {
    nodes[u].size = 1;
    for (auto [v, w] : verts[u]) {
        if (v == nodes[u].par)
            continue;
        nodes[v].dep = nodes[u].dep + 1;
        nodes[v].par = u;
        nodes[v].w = w;
        predfs(v);
        nodes[u].size += nodes[v].size;
        if (nodes[v].size > nodes[nodes[u].hson].size)
            nodes[u].hson = v;
    }
    // cerr << u << ' ' << nodes[u].par << endl;
}
int clk = 0;
void initHC(int u) {
    nodes[u].dfn = ++clk;
    bt.modify(clk, nodes[u].w);
    if (nodes[u].hson) {
        nodes[nodes[u].hson].top = nodes[u].top;
        initHC(nodes[u].hson);
    }
    for (auto [v, w] : verts[u]) {
        if (v == nodes[u].par || v == nodes[u].hson)
            continue;
        nodes[v].top = v;
        initHC(v);
    }
}
inline int getLCA(int x, int y)
{
    while (nodes[x].top != nodes[y].top) {
        // cerr << x << ' ' << y << endl;
        if (nodes[nodes[x].top].dep < nodes[nodes[y].top].dep)
            swap(x, y);
        x = nodes[nodes[x].top].par;
    }
    return nodes[x].dep < nodes[y].dep ? x : y;
}
inline int getans(int x, int tar) {
    int res = 0;
    while (nodes[x].top != nodes[tar].top) {
        letmax(res, bt.query(nodes[nodes[x].top].dfn, nodes[x].dfn));
        x = nodes[nodes[x].top].par;
    }
    return letmax(res, bt.query(nodes[tar].dfn + 1, nodes[x].dfn));
}
pair<int, int> ops[maxn];
int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    for (int i = 1; i < N; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        ops[i] = make_pair(a, b);
        verts[a].push_back(make_pair(b, w));
        verts[b].push_back(make_pair(a, w));
    }
    nodes[1].top = nodes[1].dep = 1;
    predfs(1);
    initHC(1);
    string str;
    while (true) {
        cin >> str;
        int x, y;
        if (str == "QUERY") {
            cin >> x >> y;
            const int lca = getLCA(x, y);
            cout << max(getans(x, lca), getans(y, lca)) << endl;
        } else if (str == "CHANGE") {
            cin >> x >> y;
            auto [a, b] = ops[x];
            if (nodes[b].dep > nodes[a].dep)
                swap(a, b);
            bt.modify(nodes[a].dfn, y);
        } else if (str == "DONE") {
            break;
        } else {
            assert(false);
        }
    }
    return 0;
}
