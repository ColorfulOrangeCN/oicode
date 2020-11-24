#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    long long ans = 0;
    priority_queue<int> q;
    cin >> N;
    for (int i = 1; i <= N; ++i) {
        int a;
        cin >> a;
        q.push(a);
        if (a < q.top()) {
            ans += q.top() - a;
            q.pop();
            q.push(a);
        }
    }
    cout << ans << endl;
    return 0;
}
