#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 5e4 + 1, sqn = 200;
typedef long long inte;
struct Que {
  int x1, x2, id, op;
} qs[maxn * 4];
bool operator < (const Que& a, const Que& b)
{ return (a.x1 / sqn == b.x1 / sqn) ? ((a.x1 / sqn) & 1 ? a.x2 > b.x2 : a.x2 < b.x2) : a.x1 < b.x1;}
int A[maxn];
int cnt1[maxn] = {}, cnt2[maxn] = {};
inte accum = 0;
inte ans[maxn] = {};
int main() {
  int N;
  cin >> N;
  copy_n(istream_iterator<int>(cin), N, A + 1);
  int Q;
  cin >> Q;
  int tot = 0;
  for (int i = 1; i <= Q; ++i) {
    int l1, r1, l2, r2;
    cin >> l1 >> r1 >> l2 >> r2;
    qs[tot++] = Que{r1, r2, i, 1};
    qs[tot++] = Que{r1, l2 - 1, i, -1};
    qs[tot++] = Que{l1 - 1, r2, i, -1};
    qs[tot++] = Que{l1 - 1, l2 - 1, i, 1};
  }
  for (int i = 0; i < tot; ++i)
    if (qs[i].x1 > qs[i].x2)
      swap(qs[i].x1, qs[i].x2);
  sort(qs, qs + tot);
  int L = 0, R = 0;
  for (int i = 0; i < tot; ++i) {
    while (R < qs[i].x2) {
      ++R;
      accum += cnt1[A[R]];
      ++cnt2[A[R]];
    }
    while (L < qs[i].x1) {
      ++L;
      accum += cnt2[A[L]];
      ++cnt1[A[L]];
    }
    while (R > qs[i].x2) {
      accum -= cnt1[A[R]];
      --cnt2[A[R]];
      --R;
    }
    while (L > qs[i].x1) {
      accum -= cnt2[A[L]];
      --cnt1[A[L]];
      --L;
    }
    // cerr << qs[i].x1 << ' ' << qs[i].x2 << ' ' << accum << endl;
    ans[qs[i].id] += accum * qs[i].op;
  }
  copy(ans + 1, ans + Q + 1, ostream_iterator<inte>(cout, "\n"));
  return 0;
}
