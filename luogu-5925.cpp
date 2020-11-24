#include <bits/stdc++.h>
using namespace std;

int main() {
    long long ans = 0;
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        int x, y;
        cin >> x >> y;
        ans -= x - y;
    }
    for (int i = 0; i < N; ++i) {
        int x, y;
        cin >> x >> y;
        ans += x - y;
    }
    cout << ans << endl;
    return 0;
}
