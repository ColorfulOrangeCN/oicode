#include <bits/stdc++.h>
using namespace std;

const static int maxn = 1e6 + 1;

int readint()
{
    static char c = 0;
    int v = 0;
    while (!isdigit(c))
        c = getchar();
    while(isdigit(c)) {
        v = v * 10 + c - '0';
        c = getchar();
    }
    return v;
}

int N, A[maxn];

deque<int> q1, q2;
int gmax()
{
    int v = 0;
    if (!q2.empty())
        v = max(v, q2.back());
    if (!q1.empty())
        v = max(v, q1.back());
    return v;
}
int gmin()
{
    int v = 0x3f3f3f3f;
    if (!q2.empty())
        v = min(v, q2.front());
    if (!q1.empty())
        v = min(v, q1.front());
    return v;
}

int pmax()
{
    int v = 0;
    if (!q2.empty())
        v = max(v, q2.back());
    if (!q1.empty())
        v = max(v, q1.back());
    if (!q1.empty() && v == q1.back())
        q1.pop_back();
    else
        q2.pop_back();
    return v;
}
int pmin()
{
    int v = 0x3f3f3f3f;
    if (!q2.empty())
        v = min(v, q2.front());
    if (!q1.empty())
        v = min(v, q1.front());
    if (!q1.empty() && v == q1.front())
        q1.pop_front();
    else
        q2.pop_front();
    return v;
}
int gsz()
{
    return q1.size() + q2.size();
}
void solve()
{
    q1.resize(N);
    q2.clear();
    copy(A + 1, A + N + 1, q1.begin());
    bool tag = false, ok = false;
    int ate = 0;
    for (;;) {
        if (gsz() == 1)
            goto sec1;
        {
            const int v = pmax() - pmin();
            int t = gmin();

            q2.push_front(v);
            if (v >= t)
                goto sec1;
            else
                goto sec2;
        }
    sec1:

        if (tag)
            break;
        else
            ++ate;
        continue;
    sec2:
        tag = true;
        ok = !ok;

    }
    cout << N - ate - (ok) << endl;
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    T = readint();
    --T;
    N = readint();
    for (int i = 1; i <= N; ++i)
        A[i] = readint();
    solve();
    while (T--) {
        int k;
        k = readint();
        for (int i = 0; i < k; ++i) {
            int a, b;
            a = readint();
            b = readint();
            A[a] = b;
        }
        solve();
    }
    return 0;
}
