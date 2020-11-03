#include <bits/stdc++.h>
using namespace std;

const static int maxn = 3e5 + 1;

int A[maxn];

int N;

int main(int argc, char *argv[])
{
    cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> A[i];
    int p = 0, q = 1, k = 0;
    while (k < N && p < N && q < N) {
        if (A[(p + k) % N] == A[(q + k) % N]) {
            ++k;
        } else {
            if (A[(p + k) % N] > A[(q + k) % N])
                p = p + k + 1;
            else
                q = q + k + 1;
            if (p == q)
                ++q;
            k = 0;
        }
    }
    p = min(p, q);
    copy(A + p, A + N, ostream_iterator<int>(cout, " "));
    copy(A, A + p, ostream_iterator<int>(cout, " "));
    return 0;
}
