#include <bits/stdc++.h>
using namespace std;
constexpr int maxa = 5e5 + 1, maxn = 1e5 + 1;
typedef long long inte;
set<int> buffer[maxa];
vector<int> vc[maxa];
int A[maxn];
int N, M;
struct BIT {
    int c[maxn];
    inline int lowbit(int x) {return x & (-x);}
    void add(int x, int v) {
        while (x <= N) {
            c[x] += v;
            x += lowbit(x);
        }
    }
    inte query(int x) {
        inte res = 0;
        while (x) {
            res += c[x];
            x -= lowbit(x);
        }
        return res;
    }
} bt;

int main(int argc, char *argv[])
{
    cin >> N >> M;
    copy_n(istream_iterator<int>(cin), N, A + 1);
    for (int i = 1; i <= N; ++i) {
        bt.add(i, A[i]);
        for (int j = 1; j * j <= A[i]; ++j) {
            if (A[i] % j == 0) {
                vc[j].push_back(i);
                if (j * j != A[i])
                    vc[A[i] / j].push_back(i);
            }
        }
    }
    for (int i = 1; i < maxa; ++i)
        buffer[i] = set<int>(vc[i].begin(), vc[i].end());
    for (int i = 1; i <= M; ++i) {
        int l, r, k, op;
        cin >> op;
        if (op == 1) {
            cin >> l >> r >> k;
            set<int>::iterator it1 = buffer[k].lower_bound(l), it2 = buffer[k].upper_bound(r);
            while (it1 != it2) {
                if (A[*it1] % k == 0) {
                    A[*it1] /= k;
                    bt.add(*it1, A[*it1] * (1 - k));
                    if (A[*it1] % k != 0)
                        buffer[k].erase(it1++);
                    else
                        ++it1;
                }
            }
        } else {
            cin >> l >> r;
            cout << bt.query(r) - bt.query(l - 1) << endl;
        }
    }
    return 0;
}
