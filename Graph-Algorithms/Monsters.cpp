// https://cses.fi/problemset/task/1194/

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

#define F first
#define S second

typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;

int n, m;
vector<string> grid, par, mon;
vector<vi> dist, med;

#define DR 4
int   dx[DR] = {+1, -1,  0,  0};
int   dy[DR] = { 0,  0, +1, -1};
char dir[DR] = {'D','U','R','L'};

inline bool mon_within (int x, int y) {
    return (x >= 0 && x < n && y >= 0 && y < m && (mon[x][y] == '.' || mon[x][y] == 'A'));
}

inline bool me_within (int x, int y) {
    return (x >= 0 && x < n && y >= 0 && y < m && par[x][y] == '.');
}

inline bool on_boundary (int x, int y) {
    return (x == 0 || x == n-1 || y == 0 || y == m-1);
}

void monsters_bfs () {
    queue<pii> que;
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (grid[i][j] == 'M') {
                dist[i][j] = 0;
                que.push({i, j});
            }
        }
    }
    while (!que.empty()) {
        pii u = que.front();
        que.pop();
        for (int i=0; i<DR; i++) {
            int nx = u.F+dx[i], ny = u.S+dy[i];
            if (mon_within(nx, ny)) {
                mon[nx][ny] = 'x';
                dist[nx][ny] = 1 + dist[u.F][u.S];
                que.push({nx, ny});
            }
        }
    }
}

void print_path (int dx, int dy) {
    int x = dx, y = dy;
    stack<char> path;
    while (grid[x][y] != 'A') {
        path.push(par[x][y]);
        switch (par[x][y]) {
            case 'D': x--; break;
            case 'U': x++; break;
            case 'L': y++; break;
            case 'R': y--; break;
        }
    }
    cout << path.size() << endl;
    while (!path.empty()) {
        cout << path.top();
        path.pop();
    }
    cout << endl;
}

void me_bfs (int sx, int sy) {
    queue<pii> que;
    med[sx][sy] = 0;
    que.push({sx, sy});
    while (!que.empty()) {
        pii u = que.front();
        que.pop();
        if (on_boundary(u.F, u.S)) {
            cout << "YES" << endl;
            print_path(u.F, u.S);
            return;
        }
        for (int i=0; i<DR; i++) {
            int nx = u.F+dx[i], ny = u.S+dy[i];
            if (me_within(nx, ny)) {
                med[nx][ny] = 1 + med[u.F][u.S];
                par[nx][ny] = dir[i];
                if (med[nx][ny] < dist[nx][ny]) {
                    que.push({nx, ny});
                }
            }
        }
    }
    cout << "NO" << endl;
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    cin >> n >> m;

    grid.resize(n);
    for (int i=0; i<n; i++) {
        cin >> grid[i];
    }

    dist.assign(n, vi(m, 1000005));
    mon = grid;
    monsters_bfs();

    /* for (int i=0; i<n; i++) { */
    /*     for (int j=0; j<m; j++) { */
    /*         cout << dist[i][j] << ' '; */
    /*     } */
    /*     cout << endl; */
    /* } */

    med.assign(n, vi(m));
    par = grid;
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (grid[i][j] == 'A') {
                me_bfs(i, j);
                return 0;
            }
        }
    }

    return 0;
}

