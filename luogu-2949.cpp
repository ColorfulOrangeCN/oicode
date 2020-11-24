#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> Work;
constexpr int maxn = 1e5;
Work wks[maxn];
int main() {
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> wks[i].first >> wks[i].second;
    sort(wks, wks + N);
    priority_queue<int, vector<int>, greater<int>> q;
    long long sum = 0;
    for (int i = 0; i < N; ++i) {
        q.push(wks[i].second);
        sum += wks[i].second;
        if (q.size() > wks[i].first) {
            sum -= q.top();
            q.pop();
        }
    }
    cout << sum << endl;
    return 0;
}
