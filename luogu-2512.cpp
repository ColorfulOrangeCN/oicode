#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e6;
int A[maxn];
int main(int argc, char *argv[])
{
    int n;
    cin >> n;
    copy_n(istream_iterator<int>(cin), n, A);
    transform(A, A + n, A, bind(plus<int>(), placeholders::_1 , -accumulate(A, A + n, 0) / n));
    partial_sum(A, A + n, A);
    nth_element(A, A + n / 2, A + n);
    const int v = A[n / 2];
    transform(A, A + n, A, [v](int x){return abs(x - v);});
    cout << accumulate(A, A + n, 0) << endl;
    return 0;
}
