#include <bits/stdc++.h>
using namespace std;
const static int maxn = 100;
int A[maxn], B[maxn];

int main(int argc, char *argv[])
{
    int T;
    cin >> T;
    while(T--) {
        int N, x;
        cin >> N >> x;
        for (int i = 1; i <= N; ++i)
            cin >> A[i];
        for (int i = 1; i <= N; ++i)
            cin >> B[i];
        bool f = true;
        for (int i = 1; i <= N; ++i)
            if (A[i] + B[N - i + 1] > x)
                f = false;
        if (f)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
    return 0;
}
