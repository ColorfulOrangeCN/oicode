#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 5e5 + 1;
int opts[maxn];
struct SegmentTree {
    constexpr static int memc = maxn * 4;
    struct Segment {
        int up, down, s;
    } segs[memc];
    inline static Segment gen(int op) {
        if (op == 0)
            return Segment{0, 0, 0};
            else if (op == 3)
            return Segment{1, 0, 0};
        else
            return Segment{0, 1, op - 1};
    }
    inline static Segment merge(const Segment& a, const Segment& b) {
        //assert(a.s < (1ll << a.down));
        return Segment{a.up + max(b.up - a.down, 0), b.down + max(a.down - b.up, 0), b.s + ((a.s >> b.up) << b.down)};
    }
#define lc (k * 2)
#define rc (lc + 1)
    void build(int k, int l, int r) {
        if (l == r) {
            segs[k] = gen(opts[l]);
        } else {
            const int mid = (l + r) / 2;
            build(lc, l, mid);
            build(rc, mid + 1, r);
            segs[k] = merge(segs[lc], segs[rc]);
        }
    }
    void modify(int k, int l, int r, int p, int v) {
        if (l == r) {
            segs[k] = gen(opts[l] = v);
        } else {
            const int mid = (l + r) / 2;
            if (p <= mid)
                modify(lc, l, mid, p, v);
            else
                modify(rc, mid + 1, r, p, v);
            segs[k] = merge(segs[lc], segs[rc]);
        }
    }
    Segment query(int k, int l, int r, int L, int R) {
        if (l > R || r < L)
            return gen(0);
        if (L <= l && r <= R) {
            return segs[k];
        } else {
            const int mid = (l + r) / 2;
            return merge(query(lc, l, mid, L, R), query(rc, mid + 1, r, L, R));
        }
    }
} segt;

signed main() {
    ios::sync_with_stdio(false);
    int N, M, Q;
    cin >> N >> M >> Q;
    copy_n(istream_iterator<int>(cin), M, opts + 1);
    segt.build(1, 1, M);
    for (int i = 1; i <= Q; ++i) {
        int op;
        cin >> op;
        if (op == 1) {
            int s, l, r;
            cin >> s >> l >> r;
            SegmentTree::Segment res = segt.query(1, 1, M, l, r);
            // cerr << res.up << ' ' << res.down << ' ' << res.s << endl;
            cout << ((max(s >> res.up, 1) << res.down) + res.s) << '\n';
        } else {
            int x, v;
            cin >> x >> v;
            segt.modify(1, 1, M, x, v);
        }
    }
    return 0;
}
