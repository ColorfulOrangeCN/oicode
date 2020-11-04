#include <bits/stdc++.h>
using namespace std;

signed main()
{
    int N;
    cin >> N;
    string str;
    cin >> str;
    int x1 = 0, s1 = 0, x2 = 0, s2 = 0;
    for (int i = 0; i < N / 2; ++i) {
        if (str[i] == '?')
            ++x1;
        else
            s1 += str[i] - '0';
    }
    for (int i = N / 2; i < N; ++i) {
        if (str[i] == '?')
            ++x2;
        else
            s2 += str[i] - '0';
    }
    int x = x1 - x2, s = s1 - s2;
    if (x % 2 == 0 && 9 * (x / 2) == -s) {
        cout << "Bicarp" << endl;
    } else {
        cout << "Monocarp" << endl;
    }
    return 0;
}

