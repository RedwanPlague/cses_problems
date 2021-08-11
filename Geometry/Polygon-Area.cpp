// https://cses.fi/problemset/task/2191/

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

    long long area = 0;
    for (int i = 1; i <= n; i++) {
        area += polygon[i].x * polygon[i - 1].y;
        area -= polygon[i].y * polygon[i - 1].x;
    }

    cout << abs(area) << endl;

    return 0;
}
