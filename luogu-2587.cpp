#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e5;
int A[maxn], B[maxn];
int N;
inline int solve(int *a, int *b)
{
    int ha = 1, hb = 1, ta = N, tb = N, rt = 0;
    while (ha <= ta) {
        if (a[ha] > b[hb])
            ha++, hb++, rt += 2;
        else if (a[ta] > b[tb])
            ta--, tb--, rt += 2;
        else {
            if (a[ha] == b[tb])
                rt++;
            ha++, tb--;        
        }
            
    }
    return rt;
    
}
int main(int argc, char *argv[])
{
    cin >> N;
    copy_n(istream_iterator<int>(cin), N, A + 1);
    copy_n(istream_iterator<int>(cin), N, B + 1);
    sort(A + 1, A + N + 1);
    sort(B + 1, B + N + 1);
    cout << solve(A, B) << ' ' << 2 * N - solve(B, A) << endl;
    return 0;
}
