// https://cses.fi/problemset/task/1647

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

#define N    200005
#define LOGN 18

int table[LOGN][N];
int logs[N];

void precalc() {
    for (int j = 0, till = 2, cur = 1; j < LOGN; j++, till = min(N, till << 1)) {
        while (cur < till) {
            logs[cur++] = j;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    precalc();

    int n, q;
    cin >> n >> q;

    for (int i = 0; i < n; i++) {
        cin >> table[0][i];
    }
    for (int j = 1; j <= logs[n]; j++) {
        for (int i = 0; i < n; i++) {
            table[j][i] = min(table[j - 1][i], table[j - 1][i + (1 << (j - 1))]);
        }
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        int k = logs[r - l + 1];
        cout << min(table[k][l], table[k][r - (1 << k) + 1]) << '\n';
    }

    return 0;
}
