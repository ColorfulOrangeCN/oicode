#include <bits/stdc++.h>
using namespace std;

const static int maxn = 3e6 + 1;

int A[maxn], P[maxn];

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    cin >> N;
    stack<int> st;
    for (int i = 1; i <= N; ++i) {
        cin >> A[i];
        while(!st.empty() && A[st.top()] < A[i]) {
            P[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
    copy(P + 1, P + N + 1, ostream_iterator<int>(cout, " "));
    return 0;
}
