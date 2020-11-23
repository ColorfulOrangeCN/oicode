#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 5e4 + 1, inf = 0x3f3f3f3f;
int A[maxn];
struct SegmentTree {
    struct Segment {
        int ans, lv, rv, sum;
        Segment() : ans(-inf), lv(-inf), rv(-inf), sum(0) {}
    } segs[maxn * 4];
    Segment merge(const Segment& a, const Segment& b) {
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
    void modify(int k, int l, int r, int p) {
        if (l == r) {
            segs[k].ans = segs[k].lv = segs[k].rv = segs[k].sum = A[p];
        } else {
            const int mid = (l + r) / 2;
            if (p <= mid)
                modify(lc, l, mid, p);
            else
                modify(rc, mid + 1, r, p);
            segs[k] = merge(segs[lc], segs[rc]);
        }
    }
    Segment query(int k, int l, int r, int L, int R) {
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

int main() {
    int N;
    cin >> N;
    copy_n(istream_iterator<int>(cin), N, A + 1);
    segt.build(1, 1, N);
    int M;
    cin >> M;
    for (int i = 0; i < M; ++i) {
        int a, b, op;
        cin >> op >> a >> b;
        if (op == 0)
            A[a] = b, segt.modify(1, 1, N, a);
        else
            cout << segt.query(1, 1, N, a, b).ans << endl;
    }
    return 0;
}
