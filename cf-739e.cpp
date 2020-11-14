#include <bits/stdc++.h>
using namespace std;

constexpr int maxn = 2001;
constexpr double eps = 1e-8;
int N, A, B;
struct DPSta
{
    double v;
    int a, b;
} f[maxn];
inline bool operator < (const DPSta& a, const DPSta& b) {return a.v < b.v;}
inline DPSta operator + (const DPSta& a, const DPSta& b) {
    return {a.v + b.v, a.a + b.a, a.b + b.b};
};
double u[maxn], v[maxn];
void calc(double ca, double cb) {
    f[0] = {0, 0, 0};
    for (int i = 1; i <= N; ++i)
        f[i] = max({f[i - 1], f[i - 1] + (DPSta){1 - (1 - u[i]) * (1 - v[i]) - ca - cb, 1, 1}, f[i - 1] + (DPSta){u[i] - ca, 1, 0},
            f[i - 1] + (DPSta){v[i] - cb, 0, 1}});
}
double res2;
void check2(double ca) {
    double L = 0, R = 1;
    while (R - L > eps) {
        const double mid = (L + R) / 2;
        calc(ca, mid);
        if (f[N].b < B)
            R = mid;
        else
            L = mid;
    }
    calc(ca, L);
    res2 = L;
}
int main()
{
    cin >> N >> A >> B;
    for (int i = 1; i <= N; ++i)
        cin >> u[i];
    for (int i = 1; i <= N; ++i)
        cin >> v[i];
    double L = 0, R = 1;
    while (R - L > eps) {
        const double mid = (L + R) / 2;
        check2(mid);
        if (f[N].a < A)
            R = mid;
        else
            L = mid;
    }
    check2(L);
    cout << f[N].v + A * L + B * res2 << endl;
    return 0;
}
