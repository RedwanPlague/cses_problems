#include <iostream>
#include <iomanip>
#include <cstring>
#include <algorithm>

using namespace std;

#define M 8 // size of chessboard
#define D 8 // size of direction array

int dx[D] = {+1, +1, -1, -1, +2, +2, -2, -2};
int dy[D] = {+2, -2, +2, -2, +1, -1, +1, -1};

int cnt[M][M]; // unvisited neighbor count
int sol[M][M]; // solution array, also used as visited array

struct Move {
    int x, y, ord;

    Move () {}
    Move (int x, int y, int ord)
    : x(x), y(y), ord(ord) {}

    bool operator < (const Move &m) const {
        return ord < m.ord;
    }
};

Move sorter[D];

inline bool within (const int x, const int y) {
    return (x >= 0 && x < M && y >= 0 && y < M);
}

void get_neighbor_count () {
    for (int x=0; x<M; x++) {
        for (int y=0; y<M; y++) {
            for (int i=0; i<D; i++) {
                cnt[x][y] += within(x+dx[i], y+dy[i]);
            }
        }
    }
}

void print (const int ar[M][M]) {
    for (int i=0; i<M; i++) {
        for (int j=0; j<M; j++) {
            cout << setw(2) << ar[i][j] << ' ';
            /* cout << ar[i][j] << ' '; */
        }
        cout << endl;
    }
}

bool solve (const int cx, const int cy, const int done) {
    if (done == M*M) return true;

    int nei = 0;
    for (int i=0; i<D; i++) {
        int x = cx + dx[i];
        int y = cy + dy[i];
        if (within(x, y) && sol[x][y] == -1) {
            sorter[nei++] = Move(x, y, cnt[x][y]);
        }
    }

    sort(sorter, sorter+nei);

    for (int i=0; i<nei; i++) {
        int x = sorter[i].x;
        int y = sorter[i].y;

        sol[x][y] = done+1;
        if (solve(x, y, done+1)) return true;
        sol[x][y] = -1;
    }

    return false;
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int sx, sy;
    cin >> sy >> sx;
    sx--; sy--;

    get_neighbor_count();
    memset(sol, -1, sizeof(sol));

    sol[sx][sy] = 1;
    solve(sx, sy, 1);

    print(sol);

    return 0;
}

