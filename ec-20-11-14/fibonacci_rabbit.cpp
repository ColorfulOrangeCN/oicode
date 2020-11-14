#include <bits/stdc++.h>
using namespace std;
const static int maxf = 62;
typedef long long inte;
const static inte maxv = 1e12;
inte F[maxf + 1];
void initF()
{
    F[0] = F[1] = 1;
    for (int i = 2; i <= maxf; ++i)
        F[i] = F[i - 1] + F[i - 2];
}
inline inte getfa(inte x, int& la) {
    if (x == 1 || x == 2)
        return 1;
    while (F[la - 1] >= x)
        --la;
    return x + F[la - 2] - F[la];
}

struct ReadFig {
    template<typename T>
    inline const ReadFig& operator()(T& x) const
    {
        static int c = 0;
        int op = 1;
        x = 0;
        while (!isdigit(c)) {
            if (c == '-')
                op = -1;
            c = getchar();
        }
        while (isdigit(c)) {
            x *= 10;
            x += c - '0';
            c = getchar();
        }
        x *= op;
        return *this;
    }
} readFig;

int main()
{
    freopen("fibonacci_rabbit.in", "r", stdin);
    freopen("fibonacci_rabbit.out", "w", stdout);
    initF();
    int N;
    readFig(N);
    for (int i = 1; i <= N; ++i) {
        inte a, b;
        readFig(a)(b);
        int la = maxf, lb = maxf;
        while (a != b) {
            if (a < b)
                swap(a, b), swap(la, lb);
            //cerr << a << ' ' << b << endl;
            a = getfa(a, la);
        }
        cout << a << endl;
    }
    return 0;
}