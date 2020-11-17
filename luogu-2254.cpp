#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 201;
constexpr int inf = 0x3f3f3f3f;
int N, M, X, Y, K;
char mp[maxn][maxn];
int f[maxn][maxn], D[maxn];
struct MonQue {
    typedef pair<int, int> Meta;
    deque<Meta> q;
    void push(const Meta& x) {
        while (!q.empty() && q.back().first >= x.first)
            q.pop_back();
        q.push_back(x);
    }
    void update(int l, int r) {
        while (!q.empty() && (q.front().second < l || q.front().second > r))
            q.pop_front();
    }
    int front() {
        if (q.empty())
            return inf;
        else
            return q.front().first;
    }
    void clear() {q.clear();}
};
inline bool infield(int x, int y)
{return (x > 0 && x <= N && y > 0 && y <= M);}
constexpr int dx[5] = {0, -1, 1, 0, 0}, dy[5] = {0, 0, 0, -1, 1};
void dp_line(int sec, int x, int y, int len) {
    MonQue q;
    int k = 1;
    while (infield(x, y)) {
        q.push(MonQue::Meta(f[x][y] + k, k));
        if (mp[x][y] == 'x')
            q.clear();
        q.update(k - len, k);
        f[x][y] = q.front() + len - k;
        x += dx[D[sec]];
        y += dy[D[sec]];
        ++k;
    }
}

typedef pair<int, int> Point;

int main(int argc, char *argv[])
{
    cin >> N >> M >> X >> Y >> K;
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= M; ++j)
            cin >> mp[i][j];
    memset(f, 0x3f, sizeof(f));
    f[X][Y] = 0;
    int T = 0;
    for (int j = 1; j <= K; ++j) {
        int s;
        cin >> s >> T >> D[j];
        s = T - s + 1;
        if (D[j] == 1) {
            for (int i = 1; i <= M; ++i)
                dp_line(j, N, i, s);
        } else if (D[j] == 2) {
            for (int i = 1; i <= M; ++i)
                dp_line(j, 1, i, s);
        } else if (D[j] == 3) {
            for (int i = 1; i <= N; ++i)
                dp_line(j, i, M, s);
        } else if (D[j] == 4) {
            for (int i = 1; i <= N; ++i)
                dp_line(j, i, 1, s);
        } else {
            assert(false);
        }
    }
    int ans = inf;
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= M; ++j)
            ans = min(f[i][j], ans);
    cout << T - ans << endl;
    return 0;
}
