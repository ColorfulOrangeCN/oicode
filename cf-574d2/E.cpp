#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e3 + 1;

typedef long long inte;

int N, M, A, B;

int mat[maxn][maxn];

struct MQ
{
    deque<pair<int, int> > q;
    void push(int x, int id, int lim) {
        while (!q.empty() && q.back().first > x)
            q.pop_back();
        q.push_back(make_pair(x, id));
        while(!q.empty() && q.front().second <= id - lim)
            q.pop_front();
    }
};

int cmin[maxn][maxn];

int main(int argc, char *argv[])
{
    inte g, x, y, z;
    cin >> N >> M >> A >> B;
    cin >> g >> x >> y >> z;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            mat[i][j] = g;

            g = (g * x + y) % z;
        }

    }
    MQ q;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            q.push(mat[i][j], j, B);
            cmin[i][j] = q.q.front().first;

        }
        q.q.clear();

    }
    inte ans = 0;
    for (int i = 1; i <= M; ++i) {
        for (int j = 1; j <= N; ++j) {
            q.push(cmin[j][i], j, A);

            if (i >= B && j >= A)
                ans += q.q.front().first;
        }
        q.q.clear();

    }
    cout << ans << endl;
    return 0;
}
