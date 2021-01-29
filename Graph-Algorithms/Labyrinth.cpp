// https://cses.fi/problemset/task/1193/

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

int n, m;
vector<string> grid, par;

#define DR 4
int   dx[DR] = {+1, -1,  0,  0};
int   dy[DR] = { 0,  0, +1, -1};
char dir[DR] = {'D','U','R','L'};

inline bool within (int x, int y) {
    return (x >= 0 && x < n && y >= 0 && y < m && (par[x][y] == '.' || grid[x][y] == 'B'));
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

void bfs_find_path (int sx, int sy) {
    queue<pii> que;
    que.push({sx, sy});
    while (!que.empty()) {
        pii u = que.front();
        que.pop();
        for (int i=0; i<DR; i++) {
            int nx = u.F+dx[i], ny = u.S+dy[i];
            if (within(nx, ny)) {
                par[nx][ny] = dir[i];
                if (grid[nx][ny] == 'B') {
                    cout << "YES" << endl;
                    print_path(nx, ny);
                    return;
                }
                que.push({nx, ny});
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

    par = grid;
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (grid[i][j] == 'A') {
                bfs_find_path(i, j);
                return 0;
            }
        }
    }

    return 0;
}

