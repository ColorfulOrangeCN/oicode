#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 54, mods = 30011;
int maxMat;
struct Matrix {
  int mat[maxn * 2][maxn * 2];
  Matrix() {
    memset(mat, 0, sizeof(mat));
  }
  void setEps() {
    memset(mat, 0, sizeof(mat));
    for (int i = 0; i < maxMat; ++i)
      mat[i][i] = 1;
  }
  void print() {
    for (int i = 0; i < maxMat; ++i) {
      for (int j = 0; j < maxMat; ++j)
        cerr << mat[i][j] << ' ';
      cerr << endl;
    }
  }
};
Matrix operator*(const Matrix& a, const Matrix& b) {
  Matrix res;
  for (int i = 0; i < maxMat; ++i)
    for (int j = 0; j < maxMat; ++j)
      for (int k = 0; k < maxMat; ++k)
        (res.mat[i][k] += a.mat[i][j] * b.mat[j][k]) %= mods;
  return res;
}
Matrix fpow(Matrix a, int p) {
  Matrix res;
  res.setEps();
  while (p) {
    if (p & 1)
      res = a * res;
    a = a * a;
    p >>= 1;
  }
  return res;
}
int N, M;
inline int place(int x, int y) {
  return (x + y * N);
}
int main() {
  cin >> N >> M;
  maxMat = 2 * N;
  Matrix meta, tra;
  meta.mat[0][0] = 1;
  for (int i = 0; i < N; ++i) {
    tra.mat[place(i, 0)][place(i, 0)] = 1;
    tra.mat[place(i, 0)][place(i, 1)] = 1;
    if (i)
      tra.mat[place(i, 0)][place(i - 1, 0)] = 1;
    if (i < N - 1)
      tra.mat[place(i, 0)][place(i + 1, 0)] = 1;
    tra.mat[place(i, 1)][place(i, 0)] = true;
  }
  if (M == 1)
    cout << meta.mat[place(N - 1, 0)][0] << endl;
  else
    cout << (((fpow(tra, M - 1) * meta).mat[place(N - 1, 0)][0] - (fpow(tra, M - 2) * meta).mat[place(N - 1, 1)][0]) % mods + mods) % mods<< endl;
}
