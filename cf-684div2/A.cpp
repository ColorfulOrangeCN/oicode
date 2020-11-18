#include <bits/stdc++.h>
using namespace std;

int main(){
    int T;
    cin >> T;
    while (T--) {
        int n, c[2], h;
        cin >> n >> c[0] >> c[1] >> h;
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            char f;
            cin >> f;
            f -= '0';
            ans += min(c[f], c[f ^ 1] + h);
        }
        cout << ans << endl;
    }
}
