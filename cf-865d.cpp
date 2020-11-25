#include <bits/stdc++.h>
using namespace std;

int main() {
    priority_queue<int, vector<int>, greater<int>> fan;
    int N;
    cin >> N;
    long long ans = 0;
    for (int i = 0; i < N; ++i) {
        int a;
        cin >> a;
        if (!fan.empty() && fan.top() < a) {
            ans += a - fan.top();
            fan.pop();
            fan.push(a);
        }
        fan.push(a);
    }
    cout << ans << endl;
    return 0;
}
