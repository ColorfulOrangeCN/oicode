#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5, sqn = 450;
struct Que {
    int l, r, id;
} ques[maxn];
inline bool operator < (const Que& a, const Que& b)
{return (a.l / sqn == b.l / sqn) ? ((a.l / sqn ) & 1 ? a.r > b.r : a.r < b.r) : (a.l < b.l);}

int ans[maxn];
int A[maxn];
int cnt[maxn + 1] = {0}, cur = 0;
void add(int x) {
    ++cnt[x];
    //cerr << "Add " << x << endl;
    while (cnt[cur])
        ++cur;
}
void del(int x) {
    --cnt[x];
    //cerr << "Delete "<< x << endl;
    if (!cnt[x])
        cur = min(cur, x);
}
int main(int argc, char *argv[])
{
    int N, M;
    cin >> N >> M;
    copy_n(istream_iterator<int>(cin), N, A);
    transform(A, A + N, A, [](int x){return min(x, maxn);});
    for (int i = 0; i < M; ++i) {
        cin >> ques[i].l >> ques[i].r;
        --ques[i].l, --ques[i].r;
        ques[i].id = i;
    }
    sort(ques, ques + M);
    int L = 0, R = 0;
    for (int i = 0; i < M; ++i) {
        while (R <= ques[i].r)
            add(A[R++]);
        while (R > ques[i].r + 1)
            del(A[--R]);
        while (L > ques[i].l)
            add(A[--L]);
        while (L < ques[i].l)
            del(A[L++]);
        ans[ques[i].id] = cur;
        //cerr << ques[i].l << ' ' << ques[i].r << ' ' << cur << endl;
    }
    copy(ans, ans + M, ostream_iterator<int>(cout, "\n"));
    return 0;
}
