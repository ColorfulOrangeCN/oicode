#include <bits/stdc++.h>
using namespace std;
typedef long long inte;
int main() {
    inte a;
    cin >> a;
    constexpr inte p = 1e18;
    const inte l = a - (p % a * 9 % a * 9 % a);
    cerr << l << ' ' << l + p - 1 << endl;
}
