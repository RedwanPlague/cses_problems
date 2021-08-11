// https://cses.fi/problemset/task/2193/

#include <bits/stdc++.h>

using namespace std;

struct Point {
    long long x, y;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Point> polygon(n);
    for (auto &p : polygon) {
        cin >> p.x >> p.y;
    }

    polygon.push_back(polygon[0]);

    long long A = 0, B = 0;
    for (int i = 1; i <= n; i++) {
        Point p = polygon[i], q = polygon[i - 1];
        A += p.x * q.y;
        A -= p.y * q.x;
        B += gcd(abs(p.x - q.x), abs(p.y - q.y)) + 1;
    }
    A = abs(A / 2);
    B -= n;

    cout << A - B / 2 + 1 << " " << B << endl;

    return 0;
}
