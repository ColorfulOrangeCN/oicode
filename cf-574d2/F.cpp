#include <bits/stdc++.h>
using namespace std;

const static int maxn = 3e5 + 5;

int bg[maxn], ed[maxn];

pair<int, int> org[maxn], plc[maxn], pos[maxn];
struct Que
{
    int l, r, p;
} que[maxn];
inline bool operator < (Que a, Que b) {return a.r < b.r;}

int id[maxn], la[maxn], ans[maxn];

inline int gcd(int x, int y)
{
    while (y != 0) {
        x %= y;
        swap(x, y);
    }
    return x;
}

int N, tot = 0;

#define lowbit(x) ((x) & (-(x)))
int bit[maxn];
inline void add(int x, int v)
{
    while (x <= tot) {
        bit[x] += v;
        x += lowbit(x);
    }
}
inline int query(int x)
{
    int res = 0;
    while (x) {
        res += bit[x];
        x -= lowbit(x);
    }
    return res;
}

int main()
{
    cin >> N;
    for (int i = 1; i <= N; ++i) {
        int k;
        cin >> k;
        const int bas = tot;
        bg[i] = bas;
        ed[i] = bas + k - 1;
        for (int j = 0; j < k; ++j)
            cin >> pos[tot].first >> pos[tot].second, ++tot;
        for (int j = 0; j < k; ++j) {
            const int p = bas + j, q = bas + (j + 1) % k;
            org[p].second = pos[q].second - pos[p].second;
            org[p].first = pos[q].first - pos[p].first;
            const int g = abs(gcd(org[p].first, org[p].second));
            org[p].first /= g;
            org[p].second /= g;
        }
    }
    copy(org, org + tot, plc);
    sort(plc, plc + tot);
    for (int i = 0; i < tot; ++i)
        id[i] = lower_bound(plc, plc + tot, org[i]) - plc;
    int Q;
    cin >> Q;
    for (int i = 0; i < Q; ++i)
        cin >> que[i].l >> que[i].r, que[i].p = i, que[i].r = ed[que[i].r], que[i].l = bg[que[i].l];
    sort(que, que + Q);
    int q = 0;
    for (int i = 0; i < Q; ++i) {
        while (q <= que[i].r) {
            add(q + 1, 1);
            if (la[id[q]])
                add(la[id[q]], -1);
            la[id[q]] = q + 1;
            ++q;
        }
        ans[que[i].p] = query(que[i].r + 1) - query(que[i].l); 
    }
    copy(ans, ans + Q, ostream_iterator<int>(cout, "\n"));
    return 0;
} 
