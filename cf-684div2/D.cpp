#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e5 + 1;
vector<int> verts[maxn];
bool removed[maxn];
int inner[maxn];
int nei[maxn];
int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, M, K;
        cin >> N >> M >> K;
        fill(verts + 1, verts + N + 1, vector<int>());
        fill(removed, removed + N + 1, 0);
        fill(inner, inner + N + 1, 0);
        for (int i = 0; i < M; ++i) {
            int a, b;
            cin >> a >> b;
            verts[a].push_back(b);
            verts[b].push_back(a);
            ++inner[a];
            ++inner[b];
        }
        if (K * K > 2 * M)
            continue;
        int removed_cnt = 0;
        stack<int> st;
        for (int i = 1; i <= N; ++i) {
            if (inner[i] < K)
                st.push(i), removed[i] = true;
        }
        auto try_delete =
            [&]() {
                while (!st.empty()) {
                    ++removed_cnt;
                    const int u = st.top();
                    inner[u] = 0;
                    st.pop();
                    for (int v : verts[u]) {
                        if (!removed[v])
                            --inner[v];
                        if (!removed[v] && inner[v] < K) {
                            removed[v] = true;
                            st.push(v);
                        }
                    }
                }
            };
        try_delete();
        if (N - removed_cnt != 0) {
            cout << 1 << ' ' << N - removed_cnt << endl;
            for (int i = 1; i <= N; ++i)
                if (!removed[i])
                    cout << i << ' ';
            cout << endl;
        } else {
            
        }
    }
}
