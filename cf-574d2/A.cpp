#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e3 + 1;

int A[maxn];

int main(int argc, char *argv[])
{
    int N, K;
    cin >> N >> K;
    int s = 0;
    for (int i = 1; i <= N; ++i) {
        int a;
        cin >> a;
        ++A[a];
    }
    int p = (N + 1) / 2;
    for (int i = 1; i <= K; ++i) {
        p -= A[i] / 2;
        s += A[i] / 2 * 2;
    }
    cout << p + s << endl;
    return 0;
}
