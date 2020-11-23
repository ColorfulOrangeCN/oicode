#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 2e5 + 1;
struct Node {
    int l, r, v;
} nodes[maxn];
void del(int x) {
    nodes[nodes[x].l].r = nodes[x].r;
    nodes[nodes[x].r].l = nodes[x].l;
    nodes[x].l = nodes[x].r = 0;
}
int main() {
    int N, M;
    cin >> N >> M;
    if (M > N / 2) {
        cout << "Error!" << '\n';
    } else {
        for (int i = 1; i <= N; ++i) {
            cin >> nodes[i].v;
            nodes[i].r = i + 1;
            nodes[i].l = i - 1;
        }
        nodes[1].l = N;
        nodes[N].r = 1;
        typedef pair<int, int> Hole;
        priority_queue<Hole> q;
        for (int i = 1; i <= N; ++i)
            q.push(Hole(nodes[i].v, i));
        int ans = 0, cnt = 0;
        while (cnt < M) {
            int p = q.top().first, u = q.top().second;
            q.pop();
            if (!nodes[u].l && !nodes[u].r)
                continue;
            ans += p;
            ++cnt;
            nodes[u].v = nodes[nodes[u].l].v + nodes[nodes[u].r].v - nodes[u].v;
            del(nodes[u].l);
            del(nodes[u].r);
            q.push(Hole(nodes[u].v, u));
        }
        cout << ans << endl;
    }
}
