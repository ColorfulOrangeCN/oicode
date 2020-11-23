#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 50001, maxsqn = 202, blksiz = 200;
int plc[maxn], A[maxn];
struct Solution {
    int id, v;
    Solution() : id(0), v(0) {};
    Solution(int _id, int _v) : id(_id), v(_v) {}
};
bool operator < (const Solution& a, const Solution& b)
{return a.v == b.v ? a.id > b.id : a.v < b.v;}
int pre[maxn][maxsqn];
Solution most[maxsqn][maxsqn];
int N, M;
inline int getBlock(int x) {return x / blksiz;}
int cnt[maxn] = {};
template<typename T>
inline T& letmax(T& l, const T& r) {return l < r ? l = r : l;}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> N >> M;
    copy_n(istream_iterator<int>(cin), N, A);
    copy(A, A + N, plc);
    sort(plc, plc + N);
    transform(A, A + N, A, [&](int x) -> int {return lower_bound(plc, plc + N, x) - plc;});
    const int bsize = getBlock(N - 1);
    for (int i = 0; i < N; ++i)
        ++pre[A[i]][getBlock(i)];
    for (int i = 0; i < N; ++i)
        partial_sum(pre[i], pre[i] + bsize + 1, pre[i]);
    
    for (int i = 0; i <= bsize; ++i) {
        for (int j = blksiz * i; j < N; ++j)
            letmax(most[i][getBlock(j)], Solution(A[j], pre[A[j]][getBlock(j)] - (i ? pre[A[j]][i - 1] : 0)));
        for (int j = blksiz * i; j < N; ++j)
            cnt[A[j]] = 0;
    }
    for (int i = 0; i <= bsize; ++i)
        for (int j = i + 1; j <= bsize; ++j)
            letmax(most[i][j], most[i][j - 1]);
    int x = 0;
    // cerr << plc[most[0][0].id] << ' ' << most[0][0].v << endl;
    for (int i = 1; i <= M; ++i) {
        int l, r;
        cin >> l >> r;
        l = (l + x - 1) % N;
        r = (r + x - 1) % N;
        if (l > r)
            swap(l, r);
        const int lb = getBlock(l) + 1, rb = getBlock(r) - 1;
        Solution res;
        if (lb <= rb) {
            res = most[lb][rb];
            int c = 0;
            for (int i = l; getBlock(i) < lb; ++i)
                letmax(res, Solution(A[i], ++cnt[A[i]] + pre[A[i]][rb] - pre[A[i]][lb - 1])), ++c;
            for (int i = r; getBlock(i) > rb; --i)
                letmax(res, Solution(A[i], ++cnt[A[i]] + pre[A[i]][rb] - pre[A[i]][lb - 1])), ++c;
            for (int i = l; getBlock(i) != lb; ++i)
                cnt[A[i]] = 0;
            for (int i = r; getBlock(i) != rb; --i)
                cnt[A[i]] = 0;
        } else {
            for (int i = l; i <= r; ++i)
                letmax(res, Solution(A[i], ++cnt[A[i]]));
            for (int i = l; i <= r; ++i)
                cnt[A[i]] = 0;
        }
        cout << plc[res.id] << '\n';
        x = plc[res.id];
    }
    return 0;
}
