#include <bits/stdc++.h>
using namespace std;
const int maxn = 1.5e5;
constexpr double eps = 1e-8;
template<typename T>
T& letmax(T& l, const T& r)
{return (l < r ? (l = r) : l);}

template<typename T>
T& letmin(T& l, const T& r)
{return (l > r ? (l = r) : l);}
namespace geo {
    inline bool equal(double x, double y) {return abs(x - y) - eps;}
    static double scanplc;
    struct Object {
        virtual pair<double, double> width() const = 0;
    };
    struct ObjectBorder {
        int plc;
        enum {
            upper,
            lower
        };
        ObjectBorder(int type) : plc(type) {}
        virtual double scanline(double t) const = 0;
    };
    struct Comp {
        bool operator () (const ObjectBorder* a, const ObjectBorder* b) const {
            return a->scanline(scanplc) < b->scanline(scanplc);
        }
    };
    typedef pair<double, double> Point;
    Point operator + (const Point& a, const Point& b) {return Point(a.first + b.first, a.second + b.second);}
    struct Circle : Object{
        Point p;
        double r;
        pair<double, double> width() const override {
            return make_pair(p.first - r, p.first + r);
        }
    };
    struct CircleBorder : public ObjectBorder {
        Circle *c;
        CircleBorder(Circle* _c, int type) : ObjectBorder(type), c(_c) {}
        double scanline(double t) const override {
            assert(c);
            auto [x, y] = c->p;
            assert(x - c->r <= t && t <= x + c->r);
            return y + (plc == upper ? 1: - 1) * sqrt(pow(c->r, 2) - pow(t - x, 2));
        }
    };
    struct PointObj : Object{
        Point p;
        pair<double, double> width() const override {
            return make_pair(p.first, p.first);
        }
    };
    struct PointBorder : public ObjectBorder {
        PointObj *c;
        PointBorder(PointObj *_c, int type) : ObjectBorder(type), c(_c) {}
        double scanline(double t) const override {
            assert(equal(t, c->p.first));
            return c->p.second;
        }
    };
    struct Poly : Object {
        Point p[34];
        int cnt;
        pair<double, double> width() const override {
            double l = 1e18, r = -1e18;
            for (int i = 0; i < cnt; ++i)
                letmin(l, p[i].first), letmax(r, p[i].first);
            assert(l < r);
            return make_pair(l, r);
        }
    };
    struct PolyBorder : public ObjectBorder {
        Poly *c;
        PolyBorder(PointObj *_c, int type) : ObjectBorder(type), c(_c) {}
        static double cutline(Point a, Point b, double t) {
            return a.second + (b.second - a.second) / (a.first - b.first) * (t - a.first);
        }
        static bool in(Point a, Point b, double t) {
            return (a.first <= t && t <= b.first) || (b.first <= t && t <= a.first);
        }
        double scanline(double t) const override {
            double ans = 1e18 * (plc == upper ? -1 : 1);
            for (int i = 1; i < c->cnt; ++i) {
                if (in(c->p[i - 1], c->p[i], t)) {
                    if (plc == upper)
                        letmax(ans, cutline(c->p[i - 1], c->p[i], t));
                    else
                        letmin(ans, cutline(c->p[i - 1], c->p[i], t));
                }
            }
        }
    };
}

struct Tree {
    vector<int> verts[maxn];
    int w[maxn];
    int root, clk = 0;
    struct Bit {
        int c[maxn];
        inline int lowbit(int x) {
            return x & (-x);
        }
        void addxor(int x, int v) {
            while (x < maxn) {
                c[x] ^= v;
                x += lowbit(x);
            }
        }
        int getxor(int x) {
            int res = 0;
            while (x) {
                res ^= c[x];
                x -= lowbit(x);
            }
            return res;
        }
        int rangexor(int l, int r) {
            return getxor(r) ^ getxor(l - 1);
        }
    } bt;
    struct Node {
        geo::Object* obj;
        int dep, hson, par, size, top, dfn;
    } nodes[maxn];
    void predfs(int u) {
        nodes[u].size = 1;
        for (int v : verts[u]) {
            if (v == nodes[u].par)
                continue;
            nodes[v].par = u;
            nodes[v].dep = nodes[u].dep + 1;
            predfs(v);
            nodes[u].size += nodes[v].size;
            if (nodes[nodes[u].hson].size < nodes[v].size)
                nodes[u].hson = v;
        }
    }
    void initHC(int u) {
        nodes[u].dfn = ++clk;
        if (nodes[u].hson) {
            nodes[nodes[u].hson].top = nodes[u].top;
            initHC(nodes[u].hson);
        }
        for (int v : verts[u]) {
            if (v == nodes[u].par || v == nodes[u].hson)
                continue;
            nodes[v].top = v;
            initHC(v);
        }
    }
    inline void init() {
        nodes[root].dep = nodes[root].top = 1;
        predfs(root);
        initHC(root);
    }
    int jumpxor(int u) {
        int res = 0;
        while (u) {
            res ^= bt.rangexor(nodes[nodes[u].top].dfn, nodes[u].dfn);
            u = nodes[nodes[u].top].dfn;
        }
        return res;
    }
} tree;
geo::Object *objs[maxn * 2];
int main() {
    using namespace geo;
    return 0;
}
