#include <bits/stdc++.h>
using namespace std;

const static int maxn = 1e5 + 1;

typedef long long inte;

int N, M;
int A[maxn], B[maxn];

int box[maxn * 30];

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> N >> M;
    for (int i = 1; i <= N; ++i)
        cin >> A[i];
    for (int i = 1; i <= M; ++i)
        cin >> B[i];
    int c = 0;
    sort(B + 1, B + M + 1);
    inte ans = 0;
    for (int i = 1; i <= N; ++i)
        for (int j = 0; j < 30; ++j)
            box[++c] = A[i] ^ (1 << j);
    sort(box + 1, box + c + 1);
    for (int i = 1; i <= N; ++i)
        ans -= upper_bound(B + 1, B + M + 1, A[i]) - lower_bound(B + 1, B + M + 1, A[i]);
    ans *= 30;
    for (int i = 1; i <= M; ++i)
        for (int j = 0; j < 30; ++j)
            ans += upper_bound(box + 1, box + c + 1, B[i] ^ (1 << j)) - lower_bound(box + 1, box + c + 1, B[i] ^ (1 << j));
    cout << ans / 2 << endl;
    return 0;
}
