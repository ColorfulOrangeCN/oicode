#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e5 + 1;
typedef long long inte;
inte A[maxn];
struct SegmentTree {
    struct Segment {
        inte sum, maxv;
    } segs[maxn * 4];
    inline Segment merge(const Segment& a, const Segment& b) {
        return Segment{a.sum + b.sum, max(a.maxv, b.maxv)};
    }
#define lc (k * 2)
#define rc (lc + 1)
    void build(int k, int l, int r) {
        if (l == r) {
            segs[k].sum = segs[k].maxv = A[l];
        } else {
            const int mid = (l + r) / 2;
            build(lc, l, mid);
            build(rc, mid + 1, r);
            segs[k] = merge(segs[lc], segs[rc]);
        }
    }
    void msqrt(int k, int l, int r, int L, int R) {
        if (l > R || r < L)
            return ;
        if (segs[k].maxv == 1)
            return;
        if (l == r) {
            segs[k].sum = segs[k].maxv = sqrt(segs[k].sum);
        } else {
            const int mid = (l + r) / 2;
            msqrt(lc, l, mid, L, R);
            msqrt(rc, mid + 1, r, L, R);
            segs[k] = merge(segs[lc], segs[rc]);
        }
    }
    inte query(int k, int l, int r, int L, int R) {
        if (l > R || r < L)
            return 0;
        if (L <= l && r <= R) {
            return segs[k].sum;
        } else {
            const int mid = (l + r) / 2;
            return query(lc, l, mid, L, R) + query(rc, mid + 1, r, L, R);
        }        
    }
} segt;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, T = 0;
    while (cin >> N) {
        copy_n(istream_iterator<inte>(cin), N, A + 1);
        segt.build(1, 1, N);
        int M;
        cin >> M;
        cout << "Case #" << (++T) << ":\n";
        for (int i = 0; i < M; ++i) {
            int op, a, b;
            cin >> op >> a >> b;
            if (a > b)
                swap(a, b);
            if (op) {
                cout << segt.query(1, 1, N, a, b) << '\n';
            } else {
                segt.msqrt(1, 1, N, a, b);
            }
        }
        cout << '\n';
    }
    return 0;
}
