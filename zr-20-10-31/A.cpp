#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 1;

int st[maxn];
int P[maxn], A[maxn];
int main()
{
    int N;
    cin >> N;
    int la = 0;
    bool flag = true;
    int t = 0;
    for (int i = 1; i < N; ++i)
        cin >> A[i];
    A[N] = 0;
    for (int i = 1; i <= N; ++i) {
        const int& a = A[i];
        if (a < 0 || (a & 1) || abs(a - la) > 2) {
            flag = false;
            break;
        }
        if (a - la == 2) {
            st[++t] = i;
        } else if (a == la) {
            P[i] = i;
        } else if (la - a == 2) {
            P[i] = st[t];
            P[st[t]] = i;
            --t;
        }
        la = a;
    }
    flag &= (t == 0);
    if (flag) {
        cout << "Yes" << endl;
        copy(P + 1, P + N + 1, ostream_iterator<int>(cout, " "));
    } else {
        cout << "No" << endl;
    }
    return 0;
}
