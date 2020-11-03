#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[])
{
    int N, K;
    cin >> N >> K;
    int sum = 0;
    for (int i = 1; i <= N ; ++i) {
        sum += i;
        if (sum - N + i == K) {
            cout << N - i << endl;
            break;
        }
    }
    return 0;
}
