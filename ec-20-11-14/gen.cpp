#include <bits/stdc++.h>
using namespace std;
int rrand()
{
    return (rand() << 8) + rand();
}
int main()
{
    freopen("graph.in", "w", stdout);
    srand(time(NULL));
    int N = 1e5, M = 5e5;
    cout << N << ' ' << M << endl;
    for (int i= 1; i <= M - N + 1; ++i) {
        cout << rrand() % N << ' ' << rrand() % N << endl;
    }
    for (int i = 2; i <= N; ++i) {
        cout << i << ' ' << N << endl;
    }
    return 0;
}