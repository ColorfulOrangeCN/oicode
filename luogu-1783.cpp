#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1002;
int N, M;
typedef pair<double, double> Point;
inline double getdis(Point a, Point b) {
    return sqrt((pow(a.first - b.first, 2)) + pow(a.second - b.second, 2));
}
Point pts[maxn];
double dis[maxn];
bool vis[maxn];
int main(int argc, char *argv[])
{
    cin >> N >> M;
    for (int i = 1; i <= M; ++i)
        cin >> pts[i].first >> pts[i].second;
    fill(dis, dis + M + 2, 1e18);
    dis[0] = 0;
    vis[0] = true;
    for (int i = 1; i <= M; ++i)
        dis[i] = pts[i].first;
    for (int i = 0; i <= M; ++i) {
        int k = M + 1;
        for (int i = 1; i <= M + 1; ++i) {
            if (!vis[i] && dis[i] < dis[k])
                k = i;
        }
        vis[k] = true;
        for (int i = 0; i <= M; ++i) 
            dis[i] = min(dis[i], max(dis[k], getdis(pts[i], pts[k]) / 2));
        dis[M + 1] = min(dis[M + 1], max(dis[k], N - pts[k].first));
    }
    assert(vis[M + 1]);
    cout << fixed << setprecision(2) << dis[M + 1] << endl;
    return 0;
}
