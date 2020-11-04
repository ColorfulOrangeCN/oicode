#include <bits/stdc++.h>
using namespace std;

signed main()
{
    int N;
    cin >> N;
    string a, b;
    cin >> a >> b;
    static pair<int, int> used[int(2e5 + 5)];
    int tot = 0;
    int la1 = -1, la2 = -1;
    for (int i = 0; i < N; ++i) {
        if (a[i] == 'a' && b[i] == 'b') {
            if (la1 == -1) {
                la1 = i;       
            } else {
                used[tot++] = make_pair(la1, i);
                la1 = -1;
            }
        } else if (a[i] == 'b' && b[i] == 'a'){
            if (la2 == -1) {
                la2 = i;
            } else {
                used[tot++] = make_pair(la2, i);
                la2 = -1;
            }
        }
    }
    if (la1 >= 0 && la2 >= 0) {
        used[tot++] = make_pair(la1, la1);
        used[tot++] = make_pair(la1, la2);
    } else if (la1 >= 0 || la2 >= 0)
        tot = -1;
    cout << tot << endl;
    if (tot > 0) {
        for (int i = 0; i < tot; ++i)
            cout << used[i].first + 1 << ' ' << used[i].second + 1 << endl;
    }
    return 0;
}

