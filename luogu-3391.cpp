#include <bits/stdc++.h>
using namespace std;

const static int maxn = 1e5 + 5;

int N;

struct Splay {
    struct Node {
        int v, size;
        Node *fa;
        Node *ch[2];
        bool rev;
    } nodes[maxn];
    Node *rt;
    int newp = 1;
    bool getplc(Node *cur) {
        return (cur == cur->fa->ch[1]);
    }
    void update(Node *cur) {
        if (!cur)
            return;
        cur->size = 1;
        if (cur->ch[0])
            cur->size += cur->ch[0]->size;
        if (cur->ch[1])
            cur->size += cur->ch[1]->size;
    }
    void turn(Node *cur) {
        if (cur)
            cur->rev = !cur->rev;
    }
    void pushdown(Node *cur) {
        if (!cur || !cur->rev)
            return;
        cur->rev = false;
        turn(cur->ch[0]);
        turn(cur->ch[1]);
        swap(cur->ch[0], cur->ch[1]);
    }
    void build() {
        rt = nodes;
        Node *cur = nodes;
        for (int i = 0; i <= N; ++i) {
            cur->v = i;
            cur->size = N - i + 2;
            cur->ch[1] = nodes + (newp++);
            cur->ch[1]->fa = cur;
            cur = cur->ch[1];
        }
        cur->v = N + 1;
        cur->size = 1;
    }
    void rotate(Node *cur) {
        pushdown(cur->fa->fa);
        pushdown(cur->fa);
        pushdown(cur);
        Node *fa = cur->fa;
        const bool k = getplc(cur);
        if (fa->fa) 
            fa->fa->ch[getplc(fa)] = cur;
        cur->fa = fa->fa;
        fa->ch[k] = cur->ch[k ^ 1];
        fa->fa = cur;
        if (cur->ch[k ^ 1])
            cur->ch[k ^ 1]->fa = fa;
        cur->ch[k ^ 1] = fa;
        update(fa);
        update(cur);
        assert(cur->fa != cur);
    }
    void elevate(Node *cur, Node *des) {

        while (cur->fa != des) {
            if (cur->fa->fa != des)
                rotate(getplc(cur->fa) == getplc(cur) ? cur->fa : cur);
            rotate(cur);
        }
    }
    Node* kth(Node *cur, int k) {
        pushdown(cur);
        int ls = (cur->ch[0] ? cur->ch[0]->size : 0);
        assert(cur->size > k);
        if (ls == k)
            return cur;
        else if (ls > k)
            return kth(cur->ch[0], k);
        else
            return kth(cur->ch[1], k - ls - 1);
    }
    void revReg(int l, int r) {
        debug();

        elevate(rt = kth(rt, l - 1), NULL);
        debug();
        elevate(kth(rt, r + 1), rt);
        turn(rt->ch[1]->ch[0]);
    }
    void debug() {
        /*for (int i = 0; i < newp; ++i) {
            cout << nodes + i << ' ' << nodes[i].ch[0] << ' ' << nodes[i].ch[1] << ' ' << nodes[i].v << ' ' << nodes[i].size << ' ' << nodes[i].rev << endl;
        }*/
    }
} splay;

int main(int argc, char *argv[])
{
    int M;
    cin >> N >> M;
    splay.build();
    for (int i = 0; i < M; ++i) {
        int l, r;
        cin >> l >> r;
        splay.revReg(l, r);
    }
    for (int i = 1; i <= N; ++i)
        cout << splay.kth(splay.rt, i)->v << ' ';
    return 0;
}
