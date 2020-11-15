#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 500;
int N, M;
int S[maxn] = {0};
bool check()
{
    static int tS[maxn];
    copy(S + 1, S + N + 3, tS + 1);
    for (int i = 1; i <= N + 2; ++i) {
        if (tS[i] < 0)
            return false;
        tS[i] %= 3;
        tS[i + 1] -= tS[i];
        tS[i + 2] -= tS[i];
    }
    return true;
}
int main()
{
    cin >> N >> M;
    for (int i = 1; i <= 3 * M + 1; ++i) {
        int a;
        cin >> a;
        ++S[a];
    }
    //copy(S + 1, S + N + 1, ostream_iterator<int>(cout, " "));
    bool t = true;
    for (int i = 1; i <= N; ++i) {
        ++S[i];
        bool f = false;
        for (int j = 1; j <= N && !f; ++j) {
            if (S[j] >= 2) {
                S[j] -= 2;
                f |= check();
                S[j] += 2;
            }
        }
        t &= !f;
        if (f)
            cout << i << ' ';
        --S[i];
    }
    if (t)
        cout << "NO";
    cout << endl;
    return 0;
}
