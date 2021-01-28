// https://cses.fi/problemset/task/1625/

#include <iostream>
#include <string>
#include <ctime>

using namespace std;

typedef long long ll;

#define N 7
#define M 48 // 7*7 - 1

string path;
char vis[N][N];

#define blocked(x, y)  (x < 0 || x >= N || y < 0 || y >= N || vis[x][y])

bool dead_end (int x, int y, char prev) {
    switch (prev) {
        case 'D':
            return blocked(x+1, y) && !blocked(x, y+1) && !blocked(x, y-1);
        case 'U':
            return blocked(x-1, y) && !blocked(x, y+1) && !blocked(x, y-1);
        case 'L':
            return blocked(x, y-1) && !blocked(x+1, y) && !blocked(x-1, y);
        case 'R':
            return blocked(x, y+1) && !blocked(x+1, y) && !blocked(x-1, y);
    }
    return false;
}

int travel (int i, int x, int y, char prev) {
    if (i == M) {
        if (x == N-1 && y == 0) return 1;
        return 0;
    }
    if (x == N-1 && y == 0) return 0;

    if (dead_end(x, y, prev)) return 0;

    vis[x][y] = true;

    int ret = 0;
    switch (path[i]) {
        case 'D':
            if (!blocked(x+1, y)) ret = travel(i+1, x+1, y, 'D');
            break;
        case 'U':
            if (!blocked(x-1, y)) ret = travel(i+1, x-1, y, 'U');
            break;
        case 'L':
            if (!blocked(x, y-1)) ret = travel(i+1, x, y-1, 'L');
            break;
        case 'R':
            if (!blocked(x, y+1)) ret = travel(i+1, x, y+1, 'R');
            break;
        default:
            if (!blocked(x+1, y)) ret += travel(i+1, x+1, y, 'D');
            if (!blocked(x-1, y)) ret += travel(i+1, x-1, y, 'U');
            if (!blocked(x, y-1)) ret += travel(i+1, x, y-1, 'L');
            if (!blocked(x, y+1)) ret += travel(i+1, x, y+1, 'R');
    }

    vis[x][y] = false;

    return ret;
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    cin >> path;
    /* for (int i=0; i<M; i++) path += '?'; */

    // clock_t b_time = clock();
    cout << travel(0, 0, 0, 'X') << endl;
    // clock_t e_time = clock();
    // cout << (e_time - b_time + 0.0) / CLOCKS_PER_SEC << "s" << endl;

    return 0;
}

