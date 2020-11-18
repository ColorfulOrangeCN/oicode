#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e5 + 1;
struct SegmentTree {
    struct Node {
        int sum, lazy;
    } nodes[4 * maxn];
    const static int root = 1;
#define lc (k * 2)
#define rc (lc + 1)
    inline void update(int k, int l, int r) {
        if (l != r)
            nodes[k].sum = nodes[lc].sum + nodes[rc].sum;
    }
    inline void pushdown(int k, int l, int r) {
        if (!nodes[k].lazy)
            return;
        if (l != r)
            nodes[lc].lazy = nodes[rc].lazy = nodes[k].lazy;
        nodes[k].sum = (nodes[k].lazy == 1 ? r - l + 1 : 0);
        nodes[k].lazy = 0;
    }
    void modify(int k, int l, int r, int L, int R, int v) {
        pushdown(k, l, r);
        if (l > R || r < L)
            return void();
        if (L <= l && r <= R) {
            nodes[k].lazy = v;
            pushdown(k, l, r);
        } else {
            const int mid = (l + r) / 2;
            modify(lc, l, mid, L, R, v);
            modify(rc, mid + 1, r, L, R, v);
            update(k, l, r);
        }
    }
    int query() {return nodes[root].sum;}
} segt;

struct Node {
    int par, size, hson, top, dep, deg, in, out;
} nodes[maxn];
vector<int> verts[maxn];
void predfs(int u) {
    nodes[u].size = 1;
    for (int v : verts[u]) {
        nodes[v].par = u;
        nodes[v].dep = nodes[u].dep + 1;
        predfs(v);
        nodes[u].size += nodes[v].size;
        if (nodes[v].size > nodes[nodes[u].hson].size)
            nodes[u].hson = v;
    }
}
int clk = 0;
void initHC(int u) {
    nodes[u].in = ++clk;
    if (nodes[u].hson) {
        nodes[nodes[u].hson].top = nodes[u].top;
        initHC(nodes[u].hson);
    }
    for (int v : verts[u]) {
        if (v == nodes[u].hson)
            continue;
        nodes[v].top = v;
        initHC(v);
    }
    nodes[u].out = clk;
}

int main()
{
    int N;
    cin >> N;
    for (int i = 2; i <= N; ++i) {
        int a;
        cin >> a;
        verts[a + 1].push_back(i);
    }
    predfs(1);
    nodes[1].top = 1;
    initHC(1);
    int Q;
    cin >> Q;
    int lasum = 0;
    while (Q--) {
        string opt;
        int v;
        cin >> opt >> v;
        ++v;
        if (opt == "uninstall") {
            segt.modify(SegmentTree::root, 1, clk, nodes[v].in, nodes[v].out, 2);
            cerr << nodes[v].in << ' ' << nodes[v].out << endl;
        } else {
            while (v) {
                segt.modify(SegmentTree::root, 1, clk, nodes[nodes[v].top].in, nodes[v].in, 1);


                v = nodes[nodes[v].top].par;
            }
        }
        const int q = segt.query();
        cout << abs(lasum - q) << endl;
        lasum = q;
    }
    return 0;
}

