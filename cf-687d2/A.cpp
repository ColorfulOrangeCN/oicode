 #include <bits/stdc++.h>
using namespace std;

int main()
{
  int T;
  cin >> T;
  while (T--) {
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    cout << max(n - a, a - 1) + max(m - b, b - 1) << endl;
  }
  return 0;
}
