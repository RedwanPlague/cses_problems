// https://cses.fi/problemset/task/1652

#include <iostream>

using namespace std;

#define MX 1005

int forest[MX][MX];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef REDWAN
    freopen("input.txt", "r", stdin);
#endif

    int n, q;
    cin >> n >> q;

    char s[MX];

    for (int j = 0; j <= n; j++) {
        forest[0][j] = 0;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            forest[i][j] = 0;
        }
        cin >> s;
        for (int j = 1; j <= n; j++) {
            forest[i][j] = int(s[j - 1] == '*') + forest[i - 1][j] + forest[i][j - 1] - forest[i - 1][j - 1];
        }
    }

    while (q--) {
        int r1, r2, c1, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        cout << forest[r2][c2] - forest[r2][c1 - 1] - forest[r1 - 1][c2] + forest[r1 - 1][c1 - 1] << '\n';
    }

    return 0;
}
