#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 2e5 + 1;
struct SegmentTree {
    int minv[maxn * 5];
#define lc (k * 2)
#define rc (lc + 1)
    void modify(int k, int l, int r, int p, int v) {
        if (l == r) {
            minv[k] = v;
        } else {
            const int mid = (l + r) / 2;
            if (p <= mid)
                modify(lc, l, mid, p, v);
            else
                modify(rc, mid + 1, r, p, v);
            minv[k] = min(minv[lc], minv[rc]);
        }
    }
    int query(int k, int l, int r, int lim) {
        // cerr << l << ' ' << r << ' ' << minv[k] << endl;
        if (l == r) {
            return l;
        } else {
            const int mid = (l + r) / 2;
            // cerr << minv[lc] << ' ' << minv[rc] << endl;
            if (minv[lc] < lim)
                return query(lc, l, mid, lim);
            else
                return query(rc, mid + 1, r, lim);
        }
    }
} segt;

struct Que {
    int l, r, id;
} ques[maxn];
inline bool operator < (const Que& a, const Que& b)
{return a.r < b.r;}
int A[maxn];
int ans[maxn];
int main(int argc, char *argv[])
{
    int n, m;
    cin >> n >> m;
    copy_n(istream_iterator<int>(cin), n, A + 1);
    transform(A + 1, A + n + 1, A + 1, [](int x){return min(x, maxn) + 1;});
    for (int i = 0; i < m; ++i) {
        cin >> ques[i].l >> ques[i].r;
        ques[i].id = i;
    }
    sort(ques, ques + m);
    int R = 0;
    for (int i = 0; i < m; ++i) {
        while (R <= ques[i].r)
            segt.modify(1, 1, maxn + 1, A[R], R), ++R;
        ans[ques[i].id] = segt.query(1, 1, maxn + 1, ques[i].l) - 1;
    }
    copy(ans, ans + m, ostream_iterator<int>(cout, "\n"));
    return 0;
}
