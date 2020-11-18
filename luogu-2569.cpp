#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 2e3 + 1;
typedef long long inte;
inte f[maxn][maxn];
inte AP[maxn], BP[maxn], AS[maxn], BS[maxn];

struct MonQue {
    deque<pair<int, int>> q;
    void push(pair<int, int>&& cur) {
        while (!q.empty() && q.back().first <= cur.first)
            q.pop_back();
        q.push_back(cur);
    }
    int front(int liml, int limr) {
        while (q.front().second < liml || q.front().second > limr)
            q.pop_front();
        return q.front().first;
    }
    bool empty() {return q.empty();}
};

int main(int argc, char *argv[])
{
    int T, maxP, W;
    cin >> T >> maxP >> W;
    for (int i = 1; i <= T; ++i)
        cin >> AP[i] >> BP[i] >> AS[i] >> BS[i];
    memset(f, -0x3f, sizeof(f));
    f[0][0] = 0;
    for (int i = 1; i <= T; ++i) {
        MonQue qs, qb;
        for (int p = 0; p <= maxP; ++p)
            f[i][p] = max(f[i][p], f[i - 1][p]);
        for (int p = 0; p <= maxP; ++p) {
            qb.push(make_pair(f[max(i - W - 1, 0)][p] + AP[i] * p, p));
            if (!qb.empty())
                f[i][p] = max(f[i][p], qb.front(p - AS[i], p) - AP[i] * p);
        }
        for (int p = maxP; p >= 0; --p) {
            qs.push(make_pair(f[max(i - W - 1, 0)][p] + BP[i] * p, p));
            if (!qs.empty())
                f[i][p] = max(f[i][p], qs.front(p, p + BS[i]) - BP[i] * p);
        }
    }
    cout << f[T][0] << endl;
    return 0;
}
