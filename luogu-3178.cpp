#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e5 + 1;
typedef long long inte;
int clk;
struct SegmentTree {
    struct Segment {
        inte sumv, lazy;
        Segment() : sumv(0), lazy(0) {}
    } segs[maxn * 4];
#define lc (k * 2)
#define rc (lc + 1)
    void add(int k, int l, int r, int L, int R, int v) {
        if (l > R || r < L)
            return;
        if (L <= l && r <= R) {
            segs[k].lazy += v;
        } else {
            const int mid = (l + r) / 2;
            add(lc, l, mid, L, R, v);
            add(rc, mid + 1, r, L, R, v);
        }
        segs[k].sumv = segs[k].lazy * (r - l + 1);
        if (l != r)
            segs[k].sumv += segs[lc].sumv + segs[rc].sumv;
    }
    inte query(int k, int l, int r, int L, int R, inte accum) {
        if (l > R || r < L)
            return 0;
        if (L <= l && r <= R) {
            return segs[k].sumv + accum * (r - l + 1);
        } else {
            const int mid = (l + r) / 2;
            return query(lc, l, mid, L, R, accum + segs[k].lazy) + query(rc, mid + 1, r, L, R, accum + segs[k].lazy);
        }
    }
} bt;
struct Node {
    int par, dep, size, in, out, hson, top;
} nodes[maxn];
vector<int> verts[maxn];
void predfs(int u) {
    nodes[u].size = 1;
    for (int v : verts[u]) {
        if (v == nodes[u].par)
            continue;
        nodes[v].dep = nodes[u].dep + 1;
        nodes[v].par = u;
        predfs(v);
        nodes[u].size += nodes[v].size;
        if (nodes[nodes[u].hson].size < nodes[v].size)
            nodes[u].hson = v;
    }
}
void initHC(int u) {
    nodes[u].in = ++clk;
    if (nodes[u].hson) {
        nodes[nodes[u].hson].top = nodes[u].top;
        initHC(nodes[u].hson);
    }
    for (int v : verts[u]) {
        if (v == nodes[u].hson || v == nodes[u].par)
            continue;
        nodes[v].top = v;
        initHC(v);
    }
    nodes[u].out = clk;
}

inte getAns(int x) {
    inte res = 0;
    while (x) {
        res += bt.query(1, 1, clk, nodes[nodes[x].top].in, nodes[x].in, 0);
        x = nodes[nodes[x].top].par;
    }
    return res;
}
int A[maxn];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, M;
    cin >> N >> M;
    copy_n(istream_iterator<int>(cin), N, A + 1);
    for (int i = 1; i < N; ++i) {
        int a, b;
        cin >> a >> b;
        verts[a].push_back(b);
        verts[b].push_back(a);
    }
    nodes[1].dep = nodes[1].top = 1;
    predfs(1);
    initHC(1);
    for (int i = 1; i <= N; ++i)
        bt.add(1, 1, clk, nodes[i].in, nodes[i].in, A[i]);
    for (int i = 1; i <= M; ++i) {
        int op, a, x;
        cin >> op >> a;
        if (op == 1) {
            cin >> x;
            bt.add(1, 1, clk, nodes[a].in, nodes[a].in, x);
        } else if (op == 2) {
            cin >> x;
            bt.add(1, 1, clk, nodes[a].in, nodes[a].out, x);
        } else {
            cout << getAns(a) << '\n';
        }
    }
    return 0;
}
