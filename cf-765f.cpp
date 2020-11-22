#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e5 + 1, inf = 0x3f3f3f3f;
int A[maxn];
struct SegmentTree {
    constexpr static int memc = maxn * 4;
    vector<int> segs[memc];
    int minv[memc];
#define lc (k * 2)
#define rc (lc + 1)
    void build(int k, int l, int r) {
        segs[k].resize(r - l + 1);
        copy(A + l, A + r + 1, segs[k].begin());
        sort(segs[k].begin(), segs[k].end());
        minv[k] = inf;
        if (l != r) {
            const int mid = (l + r) / 2;
            build(lc, l, mid);
            build(rc, mid + 1, r);
        }
    }
    int updated;
    void update(int k, int l, int r, int p, int x) {
        // cout << "UPDATE" << l << ' ' << r << ' ' << minv[k] << endl;
        if (r <= p) {
            auto it = upper_bound(segs[k].begin(), segs[k].end(), x);
            int upd = inf;
            if (it != segs[k].end())
                upd = min(*it - x, upd);
            if (it != segs[k].begin())
                upd = min(upd, x - *(--it));
            minv[k] = min(minv[k], upd);
            if (l == r || updated <= minv[k])
                return;
        }
        const int mid = (l + r) / 2;
        if (p > mid)
            update(rc, mid + 1, r, p, x);
        update(lc, l, mid, p, x);
        minv[k] = min({minv[k], minv[lc], minv[rc]});
        updated = min(updated, minv[k]);
    }
    int query(int k, int l, int r, int L, int R) {
        // cerr << "QUERY " << l << ' ' << r << ' ' << minv[k] << endl;
        if (l > R || r < L)
            return inf;
        if (L <= l && r <= R)
            return minv[k];
        else
            return min(query(lc, l, (l + r) / 2, L, R), query(rc, (l + r) / 2 + 1, r, L, R));
    }
} segt;

struct Que {
    int l, r, id;
} qs[maxn * 3];
inline bool operator < (const Que& a, const Que& b) {return a.r < b.r;}
int ans[maxn * 3];
int main() {
    int N;
    cin >> N;
    for (int i = 1; i <= N; ++i)
        cin >> A[i];
    segt.build(1, 1, N);
    int M;
    cin >> M;
    for (int i = 1; i <= M; ++i) {
        cin >> qs[i].l >> qs[i].r;
        qs[i].id = i;
    }
    sort(qs + 1, qs + M + 1);
    int R = 1;
    for (int i = 1; i <= M; ++i) {
        while (R < qs[i].r)
            ++R, segt.updated = inf, segt.update(1, 1, N, R - 1, A[R]);
        assert(R == qs[i].r);
        ans[qs[i].id] = segt.query(1, 1, N, qs[i].l, qs[i].r);
    }
    copy(ans + 1, ans + M + 1, ostream_iterator<int>(cout, "\n"));
    return 0;
}
