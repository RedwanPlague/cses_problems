// https://cses.fi/problemset/task/1192

#include <iostream>
#include <vector>
#include <string>

using namespace std;

void dfs (int x, int y, vector<string> &grid) {
    if (x < 0 || x >= (int)grid.size() || y < 0 || y >= (int)grid[x].size() || grid[x][y] != '.') return;

    grid[x][y] = 'x';
    dfs (x+1, y, grid);
    dfs (x-1, y, grid);
    dfs (x, y+1, grid);
    dfs (x, y-1, grid);
}

int main () {

    int n, m;
    cin >> n >> m;

    vector<string> grid(n);
    for (int i=0; i<n; i++) {
        cin >> grid[i];
    }

    int count = 0;
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (grid[i][j] == '.') {
                dfs(i, j, grid);
                count++;
            }
        }
    }

    cout << count << endl;

    return 0;
}

