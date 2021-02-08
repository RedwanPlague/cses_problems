// https://cses.fi/problemset/task/1750/

#include <iostream>

using namespace std;

#define MX 200005
#define LOGK 30

int par[MX][LOGK];

int main () {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    for (int i=1; i<=n; i++) {
        cin >> par[i][0];
    }

    for (int k=1; k<LOGK; k++) {
        for (int i=1; i<=n; i++) {
            par[i][k] = par[par[i][k-1]][k-1];
        }
    }

    while (q--) {
        int u, k;
        cin >> u >> k;
        for (int pos=LOGK-1; pos>=0; pos--) {
            if (k & (1 << pos)) {
                u = par[u][pos];
            }
        }
        cout << u << '\n';
    }

    return 0;
}

