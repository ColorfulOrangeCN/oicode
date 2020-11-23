#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e5 + 1, inf = 0x3f3f3f3f;
int A[maxn], B[maxn];
struct SegmentTree {
    struct Segment {
        int ans, lv, rv, sum, modi;
        bool cov;
        Segment() : ans(0), lv(0), rv(0), sum(0), modi(0), cov(false) {}
    } segs[maxn * 4];
    static Segment merge(const Segment& a, const Segment& b) {
        Segment res;
        res.ans = max({a.ans, b.ans, a.rv + b.lv});
        res.sum = a.sum + b.sum;
        res.rv = max(a.rv + b.sum, b.rv);
        res.lv = max(a.sum + b.lv, a.lv);
        return res;
    }
#define lc (k * 2)
#define rc (lc + 1)
    void build(int k, int l, int r) {
        if (l == r) {
            segs[k].ans = segs[k].lv = segs[k].rv = max(B[l], 0);
            segs[k].sum = B[l];
        } else {
            const int mid = (l + r) / 2;
            build(lc, l, mid);
            build(rc, mid + 1, r);
            segs[k] = merge(segs[lc], segs[rc]);
        }
    }
    void pushdown(int k, int l, int r) {
        if (!segs[k].cov)
            return;
        segs[k].sum = segs[k].modi * (r - l + 1);
        segs[k].ans = segs[k].lv = segs[k].rv = max(segs[k].sum, 0);
        if (l != r) {
            segs[lc].modi = segs[rc].modi = segs[k].modi;
            segs[lc].cov = segs[rc].cov = true;
        }
        segs[k].cov = false;
    }
    void modify(int k, int l, int r, int L, int R, int v) {
        pushdown(k, l, r);
        if (r < L || l > R)
            return;
        if (L <= l && r <= R) {
            segs[k].cov = true;
            segs[k].modi = v;
            pushdown(k, l, r);
        } else {
            const int mid = (l + r) / 2;
            modify(lc, l, mid, L, R, v);
            modify(rc, mid + 1, r, L, R, v);
            segs[k] = merge(segs[lc], segs[rc]);
        }
    }
    Segment query(int k, int l, int r, int L, int R) {
        pushdown(k, l, r);
        if (L > R)
            return Segment();
        if (l > R || r < L)
            return Segment();
        if (L <= l && r <= R) {
            return segs[k];
        } else {
            const int mid = (l + r) / 2;
            return merge(query(lc, l, mid, L, R), query(rc, mid + 1, r, L, R));
        }
    }
} segt;

struct Node {
    int par, top, size, hson, dep, dfn;
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
        if (nodes[nodes[u].hson].size < nodes[u].size)
            nodes[u].hson = v;
    }
}
int clk = 0;
void initHC(int u) {
    nodes[u].dfn = ++clk;
    if (nodes[u].hson) {
        nodes[nodes[u].hson].top = nodes[u].top;
        initHC(nodes[u].hson);
    }
    for (int v : verts[u]) {
        if (v == nodes[u].par || v == nodes[u].hson)
            continue;
        nodes[v].top = v;
        initHC(v);
    }
}

inline int getlca(int x, int y) {
    while (nodes[x].top != nodes[y].top) {
        if (nodes[nodes[x].top].dep < nodes[nodes[y].top].dep)
            swap(x, y);
        assert(x != nodes[nodes[x].top].par);
        x = nodes[nodes[x].top].par;
    }
    return (nodes[x].dep < nodes[y].dep ? x : y);
}
typedef SegmentTree::Segment Result;
inline Result jumpUpper(int x, int tar, bool vis) {
    Result res;
    while (nodes[x].top != nodes[tar].top) {
        res = SegmentTree::merge(segt.query(1, 1, clk, nodes[nodes[x].top].dfn, nodes[x].dfn), res);
        x = nodes[nodes[x].top].par;
    }
    if (vis && tar == x)
        return res;
    return SegmentTree::merge(segt.query(1, 1, clk, nodes[tar].dfn + vis, nodes[x].dfn), res);
}
inline void modify(int x, int tar, int c) {
    while (nodes[x].top != nodes[tar].top) {
        segt.modify(1, 1, clk, nodes[nodes[x].top].dfn, nodes[x].dfn, c);
        x = nodes[nodes[x].top].par;
    }
    segt.modify(1, 1, clk, nodes[tar].dfn, nodes[x].dfn, c);
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    // assert(false);
    int N;
    scanf("%d",&N);
    for (int i = 1; i <= N; ++i)
        scanf("%d", A + i);
    for (int i = 1; i < N; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        verts[a].push_back(b);
        verts[b].push_back(a);
    }
    nodes[1].dep = nodes[1].top = 1;
    predfs(1);
    initHC(1);
    for (int i = 1; i <= N; ++i) {
        B[nodes[i].dfn] = A[i];
    }
    segt.build(1, 1, clk);
    int M;
    scanf("%d", &M);
    for (int i = 1; i <= M; ++i) {
        int op, a, b;
        scanf("%d%d%d", &op, &a, &b);
        const int lca = getlca(a, b);
        if (op == 1) {
            Result seg1 = jumpUpper(a, lca, 0), seg2 = jumpUpper(b, lca, 1);
            // cerr << a << ' ' << b << ' ' << lca << endl;
            // cerr << seg1.sum << ' ' << seg2.sum << endl;
            swap(seg1.lv, seg1.rv);
            printf("%d\n", SegmentTree::merge(seg1, seg2).ans);
        } else {
            int c;
            scanf("%d", &c);
            modify(a, lca, c);
            modify(b, lca, c);
        }
    assert(clock() * 2 < CLOCKS_PER_SEC);
    }
    return 0;
}
