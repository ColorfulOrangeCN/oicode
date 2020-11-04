#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> Obj;
const int maxn = 1e5 + 1;

Obj objs[maxn];
int box[maxn];

int main(int argc, char *argv[])
{
    int T;
    cin >> T;
    while(T--) {
        int N, M;
        cin >> N;
        for (int i = 0; i < N; ++i)
            cin >> objs[i].first >> objs[i].second;
        cin >> M;
        for (int i = 0; i < M; ++i)
            cin >> box[i];
        sort(objs, objs + N);
        sort(box, box + M);
        int p = 0;
        vector<int> mark;
        for (int i = 0; i < N; ++i) {
            while(p < N && box[p] < objs[i].first)
                ++p;
            vector<int>::iterator it = upper_bound(mark.begin(), mark.end(), objs[i].second);
            if (box[p] < objs[i].first)
                break;
            if (it == mark.end()) {
                ++p;
                mark.push_back(objs[i].second);
            } else {
                *it = objs[i].second;
            }
        }
        cout << mark.size() << endl;
    }
    return 0;
}
