#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[])
{
    string s;
    cin >> s;
    int cnt0 = 0;
    for (int i = s.length() - 1; i >= 0; --i) {
        if (s[i] == '0')
            ++cnt0;
        else if (cnt0 > 0)
            --cnt0;
        else
            s[i] = '0';
    }
    cout << s << endl;
    return 0;
}
