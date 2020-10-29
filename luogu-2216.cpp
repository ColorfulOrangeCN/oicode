#include <bits/stdc++.h>
using namespace std;

const static int maxn = 1001;

int A, B, N;

int mat[maxn][maxn];

int cmax[maxn][maxn], cmin[maxn][maxn];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> A >> B >> N;
    for (int i = 1; i <= A; ++i)
        for (int j = 1; j <= B; ++j)
            cin >> mat[i][j];
    deque<pair<int, int> > qmax, qmin;
    for (int i = 1; i <= A; ++i) {
        for (int j = 1; j <= B; ++j) {
            while (!qmax.empty() && qmax.back().first <= mat[i][j])
                qmax.pop_back();
            qmax.push_back(make_pair(mat[i][j], j));
            if (qmax.front().second <= j - N)
                qmax.pop_front();
            cmax[i][j] = qmax.front().first;
            
            while (!qmin.empty() && qmin.back().first >= mat[i][j])
                qmin.pop_back();
            qmin.push_back(make_pair(mat[i][j], j));
            if (qmin.front().second <= j - N)
                qmin.pop_front();
            cmin[i][j] = qmin.front().first;
        }
        qmax.clear();
        qmin.clear();
    }
    int ans = 0x3f3f3f3f;
    for (int i = 1; i <= B; ++i) {
        for (int j = 1; j <= A; ++j) {
            while (!qmax.empty() && qmax.back().first <= cmax[j][i])
                qmax.pop_back();
            qmax.push_back(make_pair(cmax[j][i], j));
            if (qmax.front().second <= j - N)
                qmax.pop_front();
            
            while (!qmin.empty() && qmin.back().first >= cmin[j][i])
                qmin.pop_back();
            qmin.push_back(make_pair(cmin[j][i], j));
            if (qmin.front().second <= j - N)
                qmin.pop_front();
            if (i >= N && j >= N) {
                ans = min(ans, qmax.front().first - qmin.front().first);
            }
        }
        qmax.clear();
        qmin.clear();
    }
    cout << ans << endl;
    return 0;
}
