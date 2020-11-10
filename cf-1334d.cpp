#include <bits/stdc++.h>
using namespace std;
typedef long long inte;
int N;
pair<int, int> getnxt(pair<int, int> p) {
    ++p.second;
    if (p.second > N) {
        ++p.first;
        p.second = p.first + 1;
    }
    if (p.second > N)
        p.first = 1;
    return p;
}
int main(int argc, char *argv[])
{
    int T;
    cin >> T;
    while (T--) {
        inte L, R;
        cin >> N >> L >> R;
        inte p = 1;
        while (p <= N - 1 && p * (N * 2 - p - 1) <= L)
            ++p;
        --p;
        inte cur = (p - 1) * (N * 2 - p);
        for (int i = p; i < N && cur <= R; ++i) {
            for (int j = i + 1; j <= N && cur <= R; ++j) {
                ++cur;
                if (cur >= L && cur <= R)
                    cout << i << ' ';
                ++cur;
                if (cur >= L && cur <= R)
                    cout << j << ' ';
            }
        }
        if (cur < R)
            cout << 1;
        cout << endl;
    }
    return 0;
}
