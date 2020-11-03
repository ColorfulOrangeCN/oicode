#include <bits/stdc++.h>
using namespace std;
int main(int argc, char *argv[])
{
    int T;
    cin >> T;
    while(T--) {
        int N;
        cin >> N;
        int ans = 0;
        while(N--) {
            int a;
            cin >> a;
            ans ^= a;
        }
        if (ans) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}

