#include <bits/stdc++.h>
using namespace std;

int main() {
  int L = 1, R = 1e9, ans = 0;
  while (L <= R) {
    const int mid = (L + R) / 2;
    cout << mid << endl;
    int p;
    cin >> p;
    if (p > 0)
      R = mid - 1;
    else if (p < 0)
      L = mid + 1;
    else
      return 0;
  }
  return 0;
}
