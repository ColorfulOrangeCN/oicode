#include <bits/stdc++.h>
using namespace std;
typedef long long inte;
typedef long double ldd;
constexpr int maxn = 1e5 + 1;
constexpr inte maxv = 1e18, maxmulv = 1e9;
ldd fpow(ldd x, int p)
{
    ldd res = 1.0;
    while (p) {
        if (p & 1)
            res *= x;
        x *= x;
        p >>= 1;
    }
    return res;
}
void solve()
{
    static string strs[maxn];
    static ldd presum[maxn];
    static ldd f[maxn];
    static int dec[maxn];
    int N, L, P;
    cin >> N >> L >> P;
    copy_n(istream_iterator<string>(cin), N, strs + 1);
    transform(strs + 1, strs + N + 1, presum + 1, [](const string& str){return str.length();});
    partial_sum(presum + 1, presum + N + 1, presum + 1);
    deque<pair<int, int>> q;
    q.push_back(make_pair(0, 0));
    memset(f, 0, sizeof(f));
    auto getval =
        [&](int p, int i) {
            return f[p] + fpow(abs(presum[i] - presum[p] - L + i - p - 1), P);
        };
    for (int i = 1; i <= N; ++i) {
        while (q.size() > 1 && q[1].first <= i)
            q.pop_front();
        f[i] = getval(dec[i] = q.front().second, i);
        q.front().first = max(q.front().first, i + 1);
        while (!q.empty() && getval(i, q.back().first) <= getval(q.back().second, q.back().first))
            q.pop_back();
        if (q.empty()) {
            q.push_back(make_pair(i + 1, i));
        } else {
            int L = q.back().first + 1, R = N, res = N + 1;
            while (L <= R) {
                const int mid = (L + R) / 2;
                if (getval(i, mid) <= getval(q.back().second, mid)) {
                    R = mid - 1;
                    res = mid;
                } else {
                    L = mid + 1;
                }
            }
            if (res <= N)
                q.push_back(make_pair(res, i));
        }
    }
    vector<string> v;
    int cur = N;
    while (cur) {
        string str;
        for (int i = dec[cur] + 1; i <= cur; ++i)
            str += strs[i] + (i == cur ? "" : " ");
        v.push_back(str);
        cur = dec[cur];
    }
    if (f[N] > maxv)
        throw exception();
    cout << (inte)(f[N] + 0.5) << endl;
    copy(v.rbegin(), v.rend(), ostream_iterator<string>(cout, "\n"));
}

int main()
{
    int T;
    cin >> T;
    while (T--) {
        try {
            solve();
        } catch(...) {
            cout << "Too hard to arrange" << endl;
        }
        cout << "--------------------" << endl;
    }
    return 0;
}
