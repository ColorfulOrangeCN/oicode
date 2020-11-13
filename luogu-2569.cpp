#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 2e3 + 1;
int f[maxn][maxn];
int AP[maxn], BP[maxn], AS[maxn], BS[maxn];

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
};

int main(int argc, char *argv[])
{
    int T, maxP, W;
    cin >> T >> maxP >> W;
    for (int i = 1; i <= T; ++i)
        cin >> AP[i] >> BP[i] >> AS[i] >> BS[i];
    memset(f, -0x3f, sizeof(f));
    for (int i = 0; i <= min(W, T); ++i)
        for (int p = 0; p <= AS[i]; ++p)
            f[i][p] = -AP[i] * p;
    for (int i = W + 1; i <= T; ++i) {
        MonQue qs, qb;
        for (int p = 0; p <= maxP; ++p) {
            qb.push(make_pair(f[i - W - 1][p] + AP[i] * p, p));
            f[i][p] = max(max(f[i - 1][p], f[i][p]), qb.front(p - AS[i], p) - AP[i] * p);
        }
        for (int p = maxP; p >= 0; --p) {
            qs.push(make_pair(f[i - W - 1][p] + BP[i] * p, p));
            f[i][p] = max(max(f[i - 1][p], f[i][p]), qb.front(p, p + BS[i]) - BP[i] * p);
        }
    }
    cout << f[T][0] << endl;
    return 0;
}
