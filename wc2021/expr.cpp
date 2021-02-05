#define NDEBUG
#include <bits/stdc++.h>
using namespace std;
const static int maxn = 5e4 + 4, mods = 1e9 + 7;
// #define int long long
typedef long long inte;
bool hqtag = false;
int A[10][maxn];
int N, M;
struct AST {
  struct Node {
    char val;
    Node *l, *r;
    int f[10];
    Node() : val(0), l(0), r(0) {}
  } nodes[maxn];
  Node *rt;
  AST(){
    rt = 0;
  }
  inline bool checkOp(char c) {
    return c == '>' || c == '<' || c == '?';
  }
  vector<Node*> st;
  inline void ins_num(Node *ptr) {
    if (st.empty() || !st.back()) {
      st.push_back(ptr);
    } else {
      assert(st.size() >= 2);
      Node *op = st.back();
      st.pop_back();
      Node *l = st.back();
      st.pop_back();
      op->l = l;
      op->r = ptr;
      st.push_back(op);
    }
  }
  inline void deexpr(const string& str) {
    int newp = 0;
    for (int i = 0; i < str.length(); ++i) {
      const char c = str[i];
      // cerr << c << endl;
      if (isdigit(c)) {
        Node *ptr = nodes + (++newp);
        ptr->val = c;
        ins_num(ptr);
      } else if (checkOp(c)) {
        // cerr << "case2" << endl;
        Node *ptr = nodes + (++newp);
        ptr->val = c;
        st.push_back(ptr);
      } else if (c == ')') {
        // assert(false);
        Node *ptr = st.back();
        st.pop_back();
        assert(!st.back());
        st.pop_back();
        ins_num(ptr);
      } else {
        // assert(false);
        assert(c == '(');
        st.push_back(0);
      }
    }
    assert(newp < maxn);
    assert(st.size() == 1);
    rt = st.back();
  }/*
  void debug(Node *u) {
    if (isdigit(u->val)) {
      cerr << u->val;
      return;
    }
    cerr << '(';
    debug(u->l);
    cerr << ")";
    cerr << u->val;
    cerr << '(';
    debug(u->r);
    cerr << ')';
  }*/
  void run1(Node *u, int k) {
    memset(u->f, 0, sizeof(u->f));
    // cerr << u->val;
    if (isdigit(u->val)) {
      u->f[u->val - '0'] = 1;
      // cerr << "let " << u->val << endl;
    } else {
      run1(u->l, k);
      run1(u->r, k);
      for (int i = 0; i < M; ++i) {
        for (int j = 0; j < M; ++j) {
          const bool tg = A[i][k] > A[j][k];
          if (u->val != '<')
            (u->f[tg ? i : j] += ((inte)u->l->f[i]) * u->r->f[j] % mods) %= mods;
          if (u->val != '>')
            (u->f[tg ? j : i] += ((inte)u->l->f[i]) * u->r->f[j] % mods) %= mods;
        }
      }
    }
  }
  int run2(Node *u, int k) {
    if (isdigit(u->val))
      return u->val - '0';
    const int i = run2(u->l, k), j = run2(u->r, k);
    const bool tg = A[i][k] > A[j][k];
    return tg ? i : j;
  }
} ast;

signed main() {
  ifstream fin("expr.in");
  ofstream fout("expr.out");
#define cin fin
#define cout fout
  cin >> N >> M;
  for (int i = 0; i < M; ++i)
    for (int j = 0; j < N; ++j)
      cin >> A[i][j];
  string S;
  cin >> S;
  ast.deexpr(S);
  // ast.debug(ast.rt);
  // cerr << "k" << endl;
  inte ans = 0;
  if (S.find('?') != -1) {
    for (int i = 0; i < N; ++i) {
      ast.run1(ast.rt, i);
      // cerr << "gu" << endl;
      for (int j = 0; j < M; ++j)
        (ans += ((inte)ast.rt->f[j]) * A[j][i] % mods) %= mods;
    }
  } else {
    for (int i = 0; i < N; ++i)
      (ans += A[ast.run2(ast.rt, i)][i]) %= mods;
  }
  cout << ans << endl;
  // cout << (ans % mods + mods) % mods << endl;
  return 0;
}
