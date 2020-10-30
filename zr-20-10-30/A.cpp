#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 1;
struct Edge {
    int v, nxt;
} edges[maxn];
int head[maxn] = {0}, newp = 0, in[maxn];
inline void addEdge(int u, int v)
{
    edges[++newp].v = v;
    edges[newp].nxt = head[u];
    head[u] = newp;
    ++in[v];
}

int ord[maxn];

int main(int argc, char *argv[])
{
    int T;
    cin >> T;
    while(T--) {
        
        memset(ord, 0, sizeof(ord));
        memset(edges, 0, sizeof(edges));
        memset(head, 0, sizeof(head));
        memset(in, 0, sizeof(in));
        newp = 0;
        priority_queue<int> q;
        int N, M;
        cin >> N >> M;
        int tim = N;
        for (int i = 1; i <= M; ++i) {
            int a, b;
            cin >> a >> b;
            addEdge(b, a);
        }
        for (int i = 1; i <= N; ++i)
            if (!in[i])
                q.push(i);
        while (!q.empty()) {
            const int u = q.top();
            q.pop();
            ord[tim--] = u;
            for (int i = head[u]; i; i = edges[i].nxt) {
                const int v = edges[i].v;
                --in[v];
                if (!in[v])
                    q.push(v);
            }
        }
        if (tim > 0)
            cout << "Impossible!" << endl;
        else
            copy(ord + 1, ord + N + 1, ostream_iterator<int>(cout, " "));
    }
    return 0;
}
