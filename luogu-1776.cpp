#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 100, maxm = 4e4 + 1;
int v[maxn], w[maxn], m[maxn];
deque<pair<int, int>> q[maxm];
int f[maxm];
int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, W;
    cin >> N >> W;
    for (int i = 0; i < N; ++i)
        cin >> v[i] >> w[i] >> m[i];
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < w[i]; ++j)
            q[j].clear();
        for (int j = 0; j <= W; ++j) {
            auto &&cur = q[j % w[i]];
            while (!cur.empty() && cur.front().second < j - m[i] * w[i])
                cur.pop_front();
            while (!cur.empty() && cur.back().first <= f[j] - (j / w[i]) * v[i])
                cur.pop_back();
            cur.push_back(make_pair(f[j] - (j / w[i]) * v[i], j));
            f[j] = cur.front().first + (j / w[i]) * v[i];
        }
    }
    cout << f[W] << endl;
    return 0;
}
