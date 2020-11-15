#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N;
    cin >> N;
    vector<int> mark, data, f(N, 0);
    copy_n(istream_iterator<int>(cin), N, back_inserter(data));
    //reverse(data.begin(), data.end());
    for (int i = N - 1; i >= 0; --i) {
        auto it = upper_bound(begin(mark), end(mark), data[i], greater<int>());
        if (it == end(mark))
            mark.push_back(data[i]), f[i] = mark.size();
        else
            *it = data[i], f[i] = it - begin(mark) + 1;
    }
    int M;
    cin >> M;
    for (int i = 0; i < M; ++i) {
        int a;
        cin >> a;
        if (a > mark.size()) {
            cout << "Impossible" << endl;
        } else {
            int la = 0;
            for (int i = 0; i < N && a; ++i) {
                if (f[i] >= a && data[i] > la) {
                    cout << (la = data[i]) << ' ';
                    --a;
                }
            }
            cout << endl;
        }
    }
    return 0;
}
