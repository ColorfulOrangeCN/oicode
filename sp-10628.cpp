#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e5 + 1, lgn = 20;
struct SegmentBuffer {
    struct Segment {
        int times;
        Segment *l, *r;
    } segs [maxn * lgn];
    int top = 1;
    SegmentBuffer() {
        segs->times = 0;
        segs->l = segs->r = segs;
    }
    Segment* clone(const Segment* s) {return &(segs[top++] = *s);}
    Segment* null() {return segs;}
} mpl;
int N;
struct SegmentTree {
    typedef SegmentBuffer::Segment Segment;
    Segment *root;
    SegmentTree () : root(mpl.null()) {}
    void _add(Segment *&cur, int l, int r, int p, int v) {
        // cerr << "ADD" << l << ' ' << r << endl;
        cur = mpl.clone(cur);
        if (l == r) {
            cur->times += v;
        } else {
            const int mid = (l + r) / 2;
            if (p <= mid)
                _add(cur->l, l, mid, p, v);
            else
                _add(cur->r, mid + 1, r, p, v);
            cur->times = cur->l->times + cur->r->times;
        }
    }
    void add(int p, int v) {_add(root, 1, N, p, v);}
    static int kth(int l, int r, int k, Segment* a1, Segment* a2, Segment* s1, Segment* s2) {
        if (l == r) {
            return l;
        } else {
            const int mid = (l + r) / 2, lsz = a1->l->times + a2->l->times - s1->l->times - s2->l->times;
            if (lsz >= k)
                return kth(l, mid, k, a1->l, a2->l, s1->l, s2->l);
            else
                return kth(mid + 1, r, k - lsz, a1->r, a2->r, s1->r, s2->r);
        }
    }
} segts[maxn];

int plc[maxn];
int V[maxn];
vector<int> verts[maxn];
int f[maxn][lgn], dep[maxn];
void dfs(int u) {
    segts[u] = segts[f[u][0]];
    segts[u].add(V[u], 1);
    dep[u] = dep[f[u][0]] + 1;
    assert(segts[u].root->times == dep[u]);
    for (int i = 1; i < lgn && f[u][i - 1]; ++i)
        f[u][i] = f[f[u][i - 1]][i - 1];
    for (int v : verts[u]) {
        if (v != f[u][0]) {
            f[v][0] = u;
            dfs(v);
        }
    }
}
inline int getLCA(int x, int y) {
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = lgn - 1; i >= 0; --i)
        if (dep[f[x][i]] >= dep[y])
            x = f[x][i];
    if (x == y)
        return x;
    for (int i = lgn - 1; i >= 0; --i)
        if (f[x][i] != f[y][i])
            x = f[x][i], y = f[y][i];
    return f[x][0];
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int M;
    cin >> N >> M;
    copy_n(istream_iterator<int>(cin), N, V + 1);
    copy(V + 1, V + N + 1, plc + 1);
    sort(plc + 1, plc + N + 1);
    transform(V + 1, V + N + 1, V + 1, [&](int x) {return lower_bound(plc + 1, plc + N + 1, x) - plc;});
    for (int i = 1; i < N; ++i) {
        int a, b;
        cin >> a >> b;
        verts[a].push_back(b);
        verts[b].push_back(a);
    }
    dfs(1);
    for (int i = 0; i < M; ++i) {
        int u, v, k;
        cin >> u >> v >> k;
        const int lca = getLCA(u, v);
        // cerr << lca << endl;
        cout << plc[SegmentTree::kth(1, N, k, segts[u].root, segts[v].root, segts[lca].root, segts[f[lca][0]].root)] << '\n';
    }
    return 0;
}
