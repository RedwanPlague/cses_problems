// https://cses.fi/problemset/task/1739

#include <iostream>

using namespace std;

#define MX 1005

typedef long long ll;

char grid[MX][MX];
int tree[4 * MX][4 * MX];
int nx, ny;

void init_y(int vx, int lx, int rx, int vy, int ly, int ry) {
    if (ly == ry) {
        if (lx == rx) {
            tree[vx][vy] = (grid[lx - 1][ly - 1] == '*');
        }
        else {
            tree[vx][vy] = tree[2 * vx][vy] + tree[2 * vx + 1][vy];
        }
    }
    else {
        int my = (ly + ry) / 2;

        init_y(vx, lx, rx, 2 * vy, ly, my);
        init_y(vx, lx, rx, 2 * vy + 1, my + 1, ry);

        tree[vx][vy] = tree[vx][2 * vy] + tree[vx][2 * vy + 1];
    }
}

void init_x(int vx, int lx, int rx) {
    if (lx != rx) {
        int mx = (lx + rx) / 2;
        init_x(2 * vx, lx, mx);
        init_x(2 * vx + 1, mx + 1, rx);
    }
    init_y(vx, lx, rx, 1, 1, ny);
}

ll range_query_y(int vx, int vy, int ly, int ry, int by, int ey) {
    if (ey < ly || ry < by) {
        return 0;
    }
    if (by <= ly && ry <= ey) {
        return tree[vx][vy];
    }

    int my = (ly + ry) / 2;
    return range_query_y(vx, 2 * vy, ly, my, by, ey) + range_query_y(vx, 2 * vy + 1, my + 1, ry, by, ey);
}

ll range_query_x(int vx, int lx, int rx, int bx, int ex, int by, int ey) {
    if (ex < lx || rx < bx) {
        return 0;
    }
    if (bx <= lx && rx <= ex) {
        return range_query_y(vx, 1, 1, ny, by, ey);
    }

    int mx = (lx + rx) / 2;
    return range_query_x(2 * vx, lx, mx, bx, ex, by, ey) + range_query_x(2 * vx + 1, mx + 1, rx, bx, ex, by, ey);
}

void point_update_y(int vx, int lx, int rx, int vy, int ly, int ry, int y) {
    if (ly == ry && ly == y) {
        if (lx == rx) {
            tree[vx][vy] = 1 - tree[vx][vy];
        }
        else {
            tree[vx][vy] = tree[2 * vx][vy] + tree[2 * vx + 1][vy];
        }
    }
    else {
        int my = (ly + ry) / 2;
        if (y <= my) {
            point_update_y(vx, lx, rx, 2 * vy, ly, my, y);
        }
        else {
            point_update_y(vx, lx, rx, 2 * vy + 1, my + 1, ry, y);
        }
        tree[vx][vy] = tree[vx][2 * vy] + tree[vx][2 * vy + 1];
    }
}

void point_update_x(int vx, int lx, int rx, int x, int y) {
    if (lx != rx) {
        int mx = (lx + rx) / 2;
        if (x <= mx) {
            point_update_x(2 * vx, lx, mx, x, y);
        }
        else {
            point_update_x(2 * vx + 1, mx + 1, rx, x, y);
        }
    }
    point_update_y(vx, lx, rx, 1, 1, ny, y);
}

void print() {
    /* for (int i = 1; i <= nx; i++) { */
    /*     for (int j = 1; j <= ny; j++) { */
    /*         cout << (range_query_x(1, 1, nx, i, i, j, j) ? '*' : '.') << ' '; */
    /*     } */
    /*     cout << '\n'; */
    /* } */
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef REDWAN
    freopen("input.txt", "r", stdin);
#endif

    int n, q;
    cin >> n >> q;

    nx = ny = n;

    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    init_x(1, 1, nx);
    print();

    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, y;
            cin >> x >> y;
            point_update_x(1, 1, nx, x, y);
            print();
        }
        else if (op == 2) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            cout << range_query_x(1, 1, nx, x1, x2, y1, y2) << endl;
        }
    }

    return 0;
}
