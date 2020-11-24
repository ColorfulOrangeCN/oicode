#include <bits/stdc++.h>
using namespace std;
typedef long long inte;
typedef pair<inte, inte> Room;
constexpr int maxn = 1e5 + 1;
Room rms[maxn];
int main() {
    int N;
    inte M;
    cin >> N >> M;
    for (int i = 0; i < N; ++i)
        cin >> rms[i].first >> rms[i].second;
    inte la = 0, sum = 0;
    int ans = 0;
    sort(rms, rms + N);
    priority_queue<inte> q;
    for (int i = 0; i < N; ++i)  {
        sum += rms[i].first - la;
        la = rms[i].first;
        sum += rms[i].second;
        q.push(rms[i].second);
        while (!q.empty() && sum > M) {
            sum -= q.top();
            q.pop();
        }
        ans = max(ans, (int)q.size());
    }
    cout << ans << endl;
    return 0;
}
