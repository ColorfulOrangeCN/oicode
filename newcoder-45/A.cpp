#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, k;
    priority_queue<int> q;
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        q.push(a);
    }
    long long ans = 0;
    while (!q.empty()) {
        if (k <= 0 || (q.top() & 1) || q.top() == 0) {
            ans += q.top();
            q.pop();
            continue;
        }
        int t = q.top() / 2;
        q.pop();
        q.push(t);
        --k;
    }
    cout << ans << endl;
    return 0;
}
