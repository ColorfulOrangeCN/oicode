#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[])
{
    string str;
    cin >> str;
    bool f = true;
    for (int i = 1; i < str.length(); ++i) {
        if (str[i] == '1')
            f = false;
    }
    cout << (str.length() - f + 1) / 2;
    return 0;
}
