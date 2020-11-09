#include <bits/stdc++.h>
using namespace std;

const static int maxn = 1e5 + 1;
typedef long long inte;
const static inte mods = 998244353;

inte A[maxn] = {0};

int N, M;
vector<int> calls[maxn], rc[maxn];
inte ads[maxn] = {0}, addid[maxn] = {0}, muls[maxn], val[maxn];
int tps[maxn], ind[maxn] = {0};
int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> N;
    for (int i = 1; i <= N; ++i)
        cin >> A[i];
    cin >> M;
    fill(muls, muls + M + 1, 1);
    for (int i = 1; i <= M; ++i) {
        int t;
        cin >> t;
        if (t == 1) {
            cin >> addid[i] >> ads[i];
        } else if (t == 2) {
            cin >> muls[i];
        } else {
            int c;
            cin >> c;
            calls[i].resize(c);
            for (int& v : calls[i])
                cin >> v, ++ind[v];
        }
    }
    int Q;
    cin >> Q;
    calls[0].resize(Q);
    for (int& v : calls[0])
        cin >> v, ++ind[v];
    for (int i = 0; i <= M; ++i)
        for (int v : calls[i])
            rc[v].push_back(i);
    queue<int> q;
    for (int i = 0; i <= M; ++i)
        reverse(calls[i].begin(), calls[i].end());
    int tpd = 0;
    for (int i = 0; i <= M; ++i)
        if (!ind[i])
            q.push(i);
    while (!q.empty()) {
        const int u = q.front();
        q.pop();
        tps[tpd++] = u;
        for (int v : calls[u]) {
            --ind[v];
            if (!ind[v])
                q.push(v);
        }
    }
    for (int i = tpd - 1; i >= 0; --i) {
        const int u = tps[i];
        for (int v : rc[u])
            (muls[v] *= muls[u]) %= mods;
    }
    val[0] = 1;
    for (int i = 1; i <= N; ++i)
        (A[i] *= muls[0]) %= mods;
    for (int i = 0; i < tpd; ++i) {
        const int u = tps[i];
        inte mul = val[u];
        for (int v : calls[u]) {
            (val[v] += mul) %= mods;
            (mul *= muls[v]) %= mods;
        }
    }
    for (int i = 1; i <= M; ++i)
        if (addid[i])
            (A[addid[i]] += val[i] * ads[i] % mods) %= mods;
    copy(A + 1, A + N + 1, ostream_iterator<inte>(cout, " "));
    return 0;
}

/*
3
1 2 3
4
3 2 3 2
3 2 3 4
1 2 1
2 2
2
1 4
 */
