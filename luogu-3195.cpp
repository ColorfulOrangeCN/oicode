#include <bits/stdc++.h>
using namespace std;

const static int maxn = 5e4 + 1;
typedef long long inte;
int main(int argc, char *argv[])
{
    int N, L;
    cin >> N >> L;
    static inte A[maxn] = {0}, pre[maxn] = {0}, f[maxn] = {0};
    copy_n(istream_iterator<int>(cin), N, A + 1);
    partial_sum(A, A + N + 1, pre);
    auto getsum =
        [&](int l, int r) {
            return pre[r] - pre[l - 1];
        };
    auto calc = 
        [&](int l, int r) {
            return pow(getsum(l, r) + r - l - L, 2);
        };
    deque<pair<int, int> > decs;
    decs.push_back(make_pair(0, 0));
    for (int i = 1; i <= N; ++i) {
        auto getval =
            [&](int cur, int p) {
                cur = max(cur, p);
                return f[p] + calc(p + 1, cur);
            };
        const int p = (--upper_bound(decs.begin(), decs.end(), make_pair(i, 0)))->second;
        f[i] = f[p] + calc(p + 1, i);
        while (!decs.empty() && getval(decs.back().first, decs.back().second) >= getval(decs.back().first, i))
            decs.pop_back();
        if (decs.empty()) {
            decs.push_back(make_pair(i, i));
        } else {
            int L = i, R = N, res = N + 1;
            while (L <= R) {
                const int mid = (L + R) / 2;
                if (getval(mid, decs.back().second) <= getval(mid, i)) {
                    L = mid + 1;
                    res = mid;
                } else {
                    R = mid - 1;
                }
            }
            decs.push_back(make_pair(res, i));
        }
    }
    cout << f[N] << endl;
    return 0;
}
