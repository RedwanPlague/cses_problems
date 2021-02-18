// https://cses.fi/problemset/task/1687/

#include <iostream>
#include <cmath>

using namespace std;

#define N 200005
#define LGN 18

int par[N][LGN];

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    int n, lgn, q;

    cin >> n >> q;
    lgn = log2(n);

    par[0][0] = par[1][0] = 0;
    for (int i=2; i<=n; i++) {
        cin >> par[i][0];
    }

    for (int j=1; j<=lgn; j++) {
        for (int i=0; i<=n; i++) {
            par[i][j] = par[par[i][j-1]][j-1];
        }
    }

    while (q--) {
        int u, k;
        cin >> u >> k;
        for (int j=0, use=1; j<=lgn; j++, use<<=1) {
            if (k & use) {
                k ^= use;
                u = par[u][j];
            }
        }
        cout << (u == 0 ? -1 : u) << '\n';
    }

    return 0;
}

