#include <bits/stdc++.h>
using namespace std;
const static int maxn = 1e6 + 1;
struct Meta {
    int type, id;
    bool v, able;
} metas[maxn];
int newp = 0;
int plc[maxn];
vector<int> verts[maxn];
void dfs(int u)
{
    if (!metas[u].able)
        return;
    int f = 0;
    for (int v : verts[u])
        f ^= metas[v].v;
    for (int v : verts[u]) {
        if (metas[u].type == 1)
            metas[v].able = ((f ^ metas[v].v) == 1);
        else if (metas[u].type == 2)
            metas[v].able = ((f ^ metas[v].v) == 0);
        else metas[v].able = true;
        dfs(v);
    }
}
int main(int argc, char *argv[])
{
    stringstream sin;
    string str;
    getline(cin, str);
    sin.str(str);
    while (sin) {
        sin >> str;
        if (!sin)
            break;
        if (str[0] == 'x') {
            metas[newp].type = 0;
            metas[newp].id = atoi(str.substr(1, str.length() - 1).c_str());
            plc[metas[newp].id] = newp;
        } else if (str[0] == '&') {
            metas[newp].type = 1;
        } else if (str[0] == '|'){
            metas[newp].type = 2;
        } else if (str[0] == '!') {
            metas[newp].type = 3;
        }
        ++newp;
    }
    int N;
    cin >> N;
    for (int i = 1; i <= N; ++i)
        cin >> metas[plc[i]].v;
    stack<int> st;
    for (int i = 0; i < newp; ++i) {
        if (metas[i].type == 3) {
            metas[i].v = !metas[st.top()].v;
            verts[i].push_back(st.top());
            st.pop();
        } else if (metas[i].type) {
            const int a = st.top();
            st.pop();
            const int b = st.top();
            st.pop();
            metas[i].v = (metas[i].type == 1 ? (metas[a].v & metas[b].v) : (metas[a].v | metas[b].v));
            verts[i].push_back(a);
            verts[i].push_back(b);
        }
        st.push(i);
    }
    metas[st.top()].able = true;
    dfs(st.top());
    int Q;
    cin >> Q;
    for (int i = 0; i < Q; ++i) {
        int id;
        cin >> id;
        const int p = plc[id];
        if (metas[p].able)
            cout << (metas[st.top()].v ^ 1) << endl;
        else
            cout << metas[st.top()].v << endl;
    }
    return 0;
}
