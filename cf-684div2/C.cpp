#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> Point;
const int maxn = 101;
struct Op {
    Point sub[3];
} opts[maxn * maxn];
ostream& operator << (ostream& out, Point x) {
    return out << x.first << ' ' << x.second;
}
int opc = 0;
char A[maxn][maxn];
void change_upper(Point p) {
    auto [x, y] = p;
    int times = 0;
    auto method =
        [&](int a, int b) {
            A[a][b] ^= 1;
            opts[opc].sub[times++] = Point(a, b);
        };
    if (A[x][y]) method(x, y);
    if (A[x][y + 1]) method(x, y + 1);
    if (times && times < 3) method(x + 1, y);
    if (times && times < 3) method(x + 1, y + 1);
    opc += bool(times);
}
void change_left(Point p) {
    auto [x, y] = p;
    int times = 0;
    auto method =
        [&](int a, int b) {
            A[a][b] ^= 1;
            opts[opc].sub[times++] = Point(a, b);
        };
    if (A[x][y]) method(x, y);
    if (A[x + 1][y]) method(x + 1, y);
    if (times && times < 3) method(x + 1, y + 1);
    if (times && times < 3) method(x, y + 1);
    opc += bool(times);
}
void change_all(Point p) {
    constexpr int dx[] = {0, 0, 1, 1}, dy[] = {0, 1, 1, 0};
    auto [x, y] = p;
    int times = 0;
    auto method =
        [&](int a, int b) {
            A[a][b] ^= 1;
            opts[opc].sub[times++] = Point(a, b);
        };
    int cnt = 0;
    for (int i = 0; i < 4; ++i) {
        const int nx = x + dx[i], ny = y + dy[i];
        if (A[nx][ny])
            ++cnt;
    }
    if (cnt == 1) {
        int c = 2;
        for (int i = 0; i < 4; ++i) {
            const int nx = x + dx[i], ny = y + dy[i];
            if (A[nx][ny] || c)
                c -= !A[nx][ny], method(nx, ny);
        }
        ++opc;
        change_all(p);
    } else if (cnt == 2) {
        int c = 1;
        for (int i = 0; i < 4; ++i) {
            const int nx = x + dx[i], ny = y + dy[i];
            if (!A[nx][ny] || c) {
                c -= A[nx][ny];
                method(nx, ny);
            }
        }
        ++opc;
        change_all(p);
    } else if (cnt == 3) {
        for (int i = 0; i < 4; ++i) {
            const int nx = x + dx[i], ny = y + dy[i];
            if (A[nx][ny])
                method(nx, ny);
        }
        ++opc;
    } else if (cnt == 4) {
        for (int i = 1; i < 4; ++i) {
            const int nx = x + dx[i], ny = y + dy[i];
            if (A[nx][ny])
                method(nx, ny);
        }
        ++opc;
        change_all(p);
    }
}
int main() {
    int T;
    cin >> T;
    while (T--) {
        opc = 0;
        int N, M;
        cin >> N >> M;
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= M; ++j) {
                cin >> A[i][j];
                A[i][j] -= '0';
            }
        }
        for (int i = 1; i <= N - 2; ++i)
            for (int j = 1; j < M; ++j)
                change_upper(Point(i, j));
        for (int j = 1; j <= M - 2; ++j)
            change_left(Point(N - 1, j));
        change_all(Point(N - 1, M - 1));
        cout << opc << endl;
        assert(opc <= N * M);
        for (int i = 0; i < opc; ++i)
            cout << opts[i].sub[0] << ' ' << opts[i].sub[1] << ' ' << opts[i].sub[2] << endl;
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= M; ++j) {
                assert(A[i][j] == 0);
            }
        }
    }
    return 0;
}
