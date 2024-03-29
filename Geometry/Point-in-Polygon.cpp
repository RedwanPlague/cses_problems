// https://cses.fi/problemset/task/2192

// C++ routines for computational geometry.

#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

double INF = 1e100;
double EPS = 1e-12;

struct Point {
    double x, y;

    Point() {}
    Point(double x, double y) : x(x), y(y) {}

    Point operator+(const Point &p) const { return Point(x + p.x, y + p.y); }
    Point operator-(const Point &p) const { return Point(x - p.x, y - p.y); }
    Point operator*(double c) const { return Point(x * c, y * c); }
    Point operator/(double c) const { return Point(x / c, y / c); }
};

istream &operator>>(istream &in, Point &p) {
    in >> p.x >> p.y;
    return in;
}

double dot(Point p, Point q) { return p.x * q.x + p.y * q.y; }
double dist2(Point p, Point q) { return dot(p - q, p - q); }
double cross(Point p, Point q) { return p.x * q.y - p.y * q.x; }
ostream &operator<<(ostream &os, const Point &p) { return os << "(" << p.x << "," << p.y << ")"; }

// rotate a point CCW or CW around the origin
Point RotateCCW90(Point p) { return Point(-p.y, p.x); }
Point RotateCW90(Point p) { return Point(p.y, -p.x); }
Point RotateCCW(Point p, double t) { return Point(p.x * cos(t) - p.y * sin(t), p.x * sin(t) + p.y * cos(t)); }

// project point c onto line through a and b
// assuming a != b
Point ProjectPointLine(Point a, Point b, Point c) { return a + (b - a) * dot(c - a, b - a) / dot(b - a, b - a); }

// project point c onto line segment through a and b
Point ProjectPointSegment(Point a, Point b, Point c) {
    double r = dot(b - a, b - a);
    if (fabs(r) < EPS) // a = b
        return a;
    r = dot(c - a, b - a) / r;
    if (r < 0) // lower than a
        return a;
    if (r > 1) // higher than b
        return b;
    return a + (b - a) * r;
}

// compute distance from c to line through a and b, I added this
double DistancePointLine(Point a, Point b, Point c) { return sqrt(dist2(c, ProjectPointLine(a, b, c))); }

// compute distance from c to segment between a and b
double DistancePointSegment(Point a, Point b, Point c) { return sqrt(dist2(c, ProjectPointSegment(a, b, c))); }

// compute distance between point (x,y,z) and plane ax+by+cz=d
double DistancePointPlane(double x, double y, double z, double a, double b, double c, double d) {
    return fabs(a * x + b * y + c * z - d) / sqrt(a * a + b * b + c * c);
}

// determine if lines from a to b and c to d are parallel or collinear
bool LinesParallel(Point a, Point b, Point c, Point d) { return fabs(cross(b - a, c - d)) < EPS; }

bool LinesCollinear(Point a, Point b, Point c, Point d) {
    return LinesParallel(a, b, c, d) && fabs(cross(a - b, a - c)) < EPS && fabs(cross(c - d, c - a)) < EPS;
}

// determine if line segment from a to b intersects with
// line segment from c to d
bool SegmentsIntersect(Point a, Point b, Point c, Point d) {
    if (LinesCollinear(a, b, c, d)) {
        if (dist2(a, c) < EPS || dist2(a, d) < EPS || dist2(b, c) < EPS || dist2(b, d) < EPS)
            return true;
        if (dot(c - a, c - b) > 0 && dot(d - a, d - b) > 0 && dot(c - b, d - b) > 0)
            return false;
        return true;
    }
    if (cross(d - a, b - a) * cross(c - a, b - a) > 0)
        return false;
    if (cross(a - c, d - c) * cross(b - c, d - c) > 0)
        return false;
    return true;
}

// compute intersection of line passing through a and b
// with line passing through c and d, assuming that unique
// intersection exists; for segment intersection, check if
// segments intersect first
Point ComputeLineIntersection(Point a, Point b, Point c, Point d) {
    b = b - a;
    d = c - d;
    c = c - a;
    assert(dot(b, b) > EPS && dot(d, d) > EPS);
    return a + b * cross(c, d) / cross(b, d);
}

// compute center of circle given three points
Point ComputeCircleCenter(Point a, Point b, Point c) {
    b = (a + b) / 2;
    c = (a + c) / 2;
    return ComputeLineIntersection(b, b + RotateCW90(a - b), c, c + RotateCW90(a - c));
}

// determine if point is in a possibly non-convex polygon (by William
// Randolph Franklin); returns 1 for strictly interior points, 0 for
// strictly exterior points, and 0 or 1 for the remaining points.
// Note that it is possible to convert this into an *exact* test using
// integer arithmetic by taking care of the division appropriately
// (making sure to deal with signs properly) and then by writing exact
// tests for checking point on polygon boundary
bool PointInPolygon(const vector<Point> &p, Point q) {
    bool c = 0;
    for (int i = 0; i < (int)p.size(); i++) {
        int j = (i + 1) % p.size();
        if (((p[i].y <= q.y && q.y < p[j].y) || (p[j].y <= q.y && q.y < p[i].y)) &&
            q.x < p[i].x + (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y))
            c = !c;
    }
    return c;
}

// determine if point is on the boundary of a polygon
bool PointOnPolygon(const vector<Point> &p, Point q) {
    for (int i = 0; i < (int)p.size(); i++)
        if (dist2(ProjectPointSegment(p[i], p[(i + 1) % p.size()], q), q) < EPS)
            return true;
    return false;
}

// compute intersection of line through points a and b with
// circle centered at c with radius r > 0
vector<Point> CircleLineIntersection(Point a, Point b, Point c, double r) {
    vector<Point> ret;
    b = b - a;
    a = a - c;
    double A = dot(b, b);
    double B = dot(a, b);
    double C = dot(a, a) - r * r;
    double D = B * B - A * C;
    if (D < -EPS)
        return ret;
    ret.push_back(c + a + b * (-B + sqrt(D + EPS)) / A);
    if (D > EPS)
        ret.push_back(c + a + b * (-B - sqrt(D)) / A);
    return ret;
}

// compute intersection of circle centered at a with radius r
// with circle centered at b with radius R
vector<Point> CircleCircleIntersection(Point a, Point b, double r, double R) {
    vector<Point> ret;
    double d = sqrt(dist2(a, b));
    if (d > r + R || d + min(r, R) < max(r, R))
        return ret;
    double x = (d * d - R * R + r * r) / (2 * d);
    double y = sqrt(r * r - x * x);
    Point v = (b - a) / d;
    ret.push_back(a + v * x + RotateCCW90(v) * y);
    if (y > 0)
        ret.push_back(a + v * x - RotateCCW90(v) * y);
    return ret;
}

// This code computes the area or centroid of a (possibly nonconvex)
// polygon, assuming that the coordinates are listed in a clockwise or
// counterclockwise fashion.  Note that the centroid is often known as
// the "center of gravity" or "center of mass".
double ComputeSignedArea(const vector<Point> &p) {
    double area = 0;
    for (int i = 0; i < (int)p.size(); i++) {
        int j = (i + 1) % p.size();
        area += p[i].x * p[j].y - p[j].x * p[i].y;
    }
    return area / 2.0;
}

double ComputeArea(const vector<Point> &p) { return fabs(ComputeSignedArea(p)); }

Point ComputeCentroid(const vector<Point> &p) {
    Point c(0, 0);
    double scale = 6.0 * ComputeSignedArea(p);
    for (int i = 0; i < (int)p.size(); i++) {
        int j = (i + 1) % p.size();
        c = c + (p[i] + p[j]) * (p[i].x * p[j].y - p[j].x * p[i].y);
    }
    return c / scale;
}

// tests whether or not a given polygon (in CW or CCW order) is simple
bool IsSimple(const vector<Point> &p) {
    for (int i = 0; i < (int)p.size(); i++) {
        for (int k = i + 1; k < (int)p.size(); k++) {
            int j = (i + 1) % p.size();
            int l = (k + 1) % p.size();
            if (i == l || j == k)
                continue;
            if (SegmentsIntersect(p[i], p[j], p[k], p[l]))
                return false;
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<Point> poly(n);
    for (auto &x : poly) {
        cin >> x;
    }
    while (m--) {
        Point p;
        cin >> p;
        if (PointOnPolygon(poly, p)) {
            cout << "BOUNDARY" << '\n';
        }
        else if (PointInPolygon(poly, p)) {
            cout << "INSIDE" << '\n';
        }
        else {
            cout << "OUTSIDE" << '\n';
        }
    }

    return 0;
}
