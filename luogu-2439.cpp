#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e4 + 1, tim = 30000;

vector<int> la[maxn];

int f[maxn] = {0};

int main(int argc, char *argv[])
{
    int N;
    cin >> N;
    for (int i = 1; i <= N; ++i) {
        int l, r;
        cin >> l >> r;
        la[r].push_back(l);
    }
    for (int i = 1; i <= tim; ++i) {
        f[i] = f[i - 1];
        for (int j = 0; j < la[i].size(); ++j)
            f[i] = max(f[i], f[la[i][j]] + i - la[i][j]);
    }
    cout << f[tim] << endl;
    return 0;
}
