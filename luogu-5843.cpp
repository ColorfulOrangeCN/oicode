#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5;
constexpr double eps = 1e-8;

namespace geo {
    inline bool equal(double x, double y) {return abs(x - y) - eps;}
    static double scanplc;
    struct Object {};
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
    struct Circle {
        Point p;
        double r;
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
    struct PointObj {
        Point p;
    };
    struct PointBorder : public ObjectBorder {
        PointObj *c;
        PointBorder(PointObj *_c, int type) : ObjectBorder(type), c(_c) {}
        double scanline(double t) const override {
            assert(equal(t, c->p.first));
            return c->p.second;
        }
    };
}

struct Tree {
    vector<int> verts[maxn];
    int w[maxn];
    int root, clk = 0;
    struct Node {
        int dep, hson, par, size, top, dfn;
    } nodes[maxn];
    void predfs(int u) {
        nodes[u].size = 1;
        for (int v : verts[u]) {
            if (v == nodes[u].par)
                continue;
            nodes[v].par = u;
            nodes[v].dep = nodes[u].dep + 1;
        }
    }
} tree;

int main() {
    return 0;
}
