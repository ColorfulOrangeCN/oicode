#include <bits/stdc++.h>
using namespace std;
typedef long long inte;
constexpr int maxn = 5e5 + 1;
constexpr inte inf = 0x3f3f3f3f3f3f3f3f;

struct MonQue {
    deque<pair<inte, int>> q;
    void push(pair<inte, int>&& cur) {
        while (!q.empty() && q.back().first <= cur.first)
            q.pop_back();
        q.push_back(cur);
            
    }
    inte front(int liml) {
        while (!q.empty() && q.front().second < liml)
            q.pop_front();
        if (q.empty())
            return -inf;
        return q.front().first;    
    }
};
inte f[maxn], A[maxn], x[maxn];
int N, D, K;
bool check(int g)
{
    f[0] = 0;
    const int gl = D + g, gr = max(D - g, 1);
    MonQue q;
    inte ans = -inf;
    int p = 0;
    for (int i = 1; i <= N; ++i) {
        while (x[p] <= x[i] - gr)
            q.push(make_pair(f[p], x[p])), ++p;
        f[i] = q.front(x[i] - gl) + A[i];
        ans = max(ans, f[i]);
    }
    return ans >= K;
}

int main(int argc, char *argv[])
{
    cin >> N >> D >> K;
    for (int i = 1; i <= N; ++i)
        cin >> x[i] >> A[i];
    int L = 0, R = x[N];
    int ans = 0x3f3f3f3f;
    while (L <= R) {
        const int mid = (L + R) / 2;
        if (check(mid)) {
            R = mid - 1;
            ans = mid;
        } else {
            L = mid + 1;
        }
    }
    if (ans >= 0x3f3f3f3f)
        cout << -1 << endl;
    else
        cout << ans << endl;
    return 0;
}

