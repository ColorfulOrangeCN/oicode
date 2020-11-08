#include <bits/stdc++.h>
using namespace std;

bool disable[26][26];

int g[26] = {0};

signed main()
{
    int N;
    string str;
    cin >> N >> str;
    int M;
    cin >> M;
    for (int i = 1; i <= M; ++i) {
        char a, b;
        cin >> a >> b;
        disable[a - 'a'][b - 'a'] = disable[b - 'a'][a - 'a'] = true;
    }
    int f;
    for (int i = 1; i <= N; ++i) {
        f = 0x3f3f3f3f;
        for (int j = 0; j < 26; ++j) {
            if (disable[j][str[i - 1] - 'a'])
                continue;
            f = min(f, g[j] + i - 1);
        }
        g[str[i - 1] - 'a'] = min(g[str[i - 1] - 'a'], f - i);
    }
    cout << f << endl;
    return 0;
}

