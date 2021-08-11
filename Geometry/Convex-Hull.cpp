// https://cses.fi/problemset/task/2195

// Compute the 2D convex hull of a set of points using the monotone chain
// algorithm.  Eliminate redundant points from the hull if REMOVE_REDUNDANT is
// #defined.
//
// Running time: O(n log n)
//
//   INPUT:   a vector of input points, unordered.
//   OUTPUT:  a vector of points in the convex hull, counterclockwise, starting
//            with bottommost/leftmost point

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

#define REMOVE_REDUNDANT

typedef double T;
const T EPS = 1e-7;

struct Point {
    T x, y;
    Point() {}
    Point(T x, T y) : x(x), y(y) {}
    bool operator<(const Point &rhs) const { return make_pair(y, x) < make_pair(rhs.y, rhs.x); }
    bool operator==(const Point &rhs) const { return make_pair(y, x) == make_pair(rhs.y, rhs.x); }
};

T cross(Point p, Point q) { return p.x * q.y - p.y * q.x; }

T area2(Point a, Point b, Point c) { return cross(a, b) + cross(b, c) + cross(c, a); }

#ifdef REMOVE_REDUNDANT
bool between(const Point &a, const Point &b, const Point &c) {
    return (fabs(area2(a, b, c)) < EPS && (a.x - b.x) * (c.x - b.x) <= 0 && (a.y - b.y) * (c.y - b.y) <= 0);
}
#endif

void ConvexHull(vector<Point> &pts) {
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());
    vector<Point> up, dn;
    for (int i = 0; i < (int)pts.size(); i++) {
        while (up.size() > 1 && area2(up[up.size() - 2], up.back(), pts[i]) >= 0)
            up.pop_back();
        while (dn.size() > 1 && area2(dn[dn.size() - 2], dn.back(), pts[i]) <= 0)
            dn.pop_back();
        up.push_back(pts[i]);
        dn.push_back(pts[i]);
    }
    pts = dn;
    for (int i = (int)up.size() - 2; i >= 1; i--)
        pts.push_back(up[i]);

#ifdef REMOVE_REDUNDANT
    if (pts.size() <= 2)
        return;
    dn.clear();
    dn.push_back(pts[0]);
    dn.push_back(pts[1]);
    for (int i = 2; i < (int)pts.size(); i++) {
        if (between(dn[dn.size() - 2], dn[dn.size() - 1], pts[i]))
            dn.pop_back();
        dn.push_back(pts[i]);
    }
    if (dn.size() >= 3 && between(dn.back(), dn[0], dn[1])) {
        dn[0] = dn.back();
        dn.pop_back();
    }
    pts = dn;
#endif
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Point> poly(n);
    for (auto &p : poly) {
        cin >> p.x >> p.y;
    }
    ConvexHull(poly);

    cout << poly.size() << '\n';
    for (auto &p : poly) {
        cout << p.x << ' ' << p.y << '\n';
    }

    return 0;
}
