#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 5e5 + 1, inf = 0x3f3f3f3f;
#define int long long
int A[maxn];
struct SegmentTree {
    struct Segment {
        int ans, lv, rv, sum, modi;
        bool cov;
        Segment() : ans(-inf), lv(-inf), rv(-inf), sum(0), modi(0), cov(false) {}
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
            segs[k].ans = segs[k].lv = segs[k].rv = segs[k].sum = A[l];
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
        segs[k].ans = segs[k].lv = segs[k].rv = max(segs[k].sum, segs[k].modi);
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
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    copy_n(istream_iterator<long long>(cin), N, A + 1);
    for (int i = 1; i <= N; ++i)
        segt.modify(1, 1, N, i, i, A[i]);
    int M;
    cin >> M;
    for (int i = 1; i <= M; ++i) {
        int op, a, b;
        cin >> op >> a >> b;
        if (a > b)
            swap(a, b);
        if (op == 1) {
            cout << segt.query(1, 1, N, a, b).ans << '\n';
        } else {
            segt.modify(1, 1, N, a, a, b);
        }
    }
    return 0;
}
